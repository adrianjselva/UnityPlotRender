#include "PlatformBase.h"
#include "RenderAPI.h"

#include <cassert>
#include <cmath>
#include <vector>

static float g_Time;
static void* g_TextureHandle = nullptr;
static int g_TextureWidth;
static int g_TextureHeight;
static IUnityInterfaces* s_UnityInterfaces = nullptr;
static IUnityGraphics* s_Graphics = nullptr;
static RenderAPI* s_CurrentAPI = nullptr;
static UnityGfxRenderer s_DeviceType = kUnityGfxRendererNull;

static void UNITY_INTERFACE_API OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType);
static void UNITY_INTERFACE_API OnRenderEvent(int eventID);
static void writePlotToTexture();

extern "C" UnityRenderingEvent UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetRenderEventFunc() {
    return OnRenderEvent;
}

static void UNITY_INTERFACE_API OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType) {
    // Create graphics API implementation upon initialization
    if (eventType == kUnityGfxDeviceEventInitialize) {
        assert(s_CurrentAPI == nullptr);
        s_DeviceType = s_Graphics->GetRenderer();
        s_CurrentAPI = CreateRenderAPI(s_DeviceType);
    }

    // Let the implementation process the device related events
    if (s_CurrentAPI) {
        s_CurrentAPI->ProcessDeviceEvent(eventType, s_UnityInterfaces);
    }

    // Cleanup graphics API implementation upon shutdown
    if (eventType == kUnityGfxDeviceEventShutdown) {
        delete s_CurrentAPI;
        s_CurrentAPI = nullptr;
        s_DeviceType = kUnityGfxRendererNull;
    }
}

static void UNITY_INTERFACE_API OnRenderEvent(int eventID) {
    if (s_CurrentAPI == nullptr) {
        return;
    }

    writePlotToTexture();
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces* unityInterfaces) {
    s_UnityInterfaces = unityInterfaces;
    s_Graphics = s_UnityInterfaces->Get<IUnityGraphics>();
    s_Graphics->RegisterDeviceEventCallback(OnGraphicsDeviceEvent);

    OnGraphicsDeviceEvent(kUnityGfxDeviceEventInitialize);
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginUnload() {
    s_Graphics->UnregisterDeviceEventCallback(OnGraphicsDeviceEvent);
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
setTextureFromUnity(void* textureHandle, int width, int height) {
    // Called at initialization time

    g_TextureHandle = textureHandle;
    g_TextureWidth = width;
    g_TextureHeight = height;
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API setTimeFromUnity(float time) {
    g_Time = time;
}
// --------------------------------------------------------------------------
// OnRenderEvent
// This will be called for GL.IssuePluginEvent script calls; eventID will
// be the integer passed to IssuePluginEvent. In this example, we just ignore
// that value.

static void writePlotToTexture() {
    void* textureHandle = g_TextureHandle;
    int width = g_TextureWidth;
    int height = g_TextureHeight;

    if(!textureHandle) {
        return;
    }

    int textureRowPitch;
    void* textureDataPtr = s_CurrentAPI->BeginModifyTexture(textureHandle, width, height, &textureRowPitch);
    if (!textureDataPtr) {
        return;
    }

    const float t = g_Time * 4.0f;

    auto* dst = (unsigned char*)textureDataPtr;
    for (int y = 0; y < height; ++y) {
        unsigned char* ptr = dst;
        for (int x = 0; x < width; ++x) {
            // Simple "plasma effect": several combined sine waves
            int vv = int(
                    (127.0f + (127.0f * sinf((float) x / 7.0f + t))) +
                    (127.0f + (127.0f * sinf((float) y / 5.0f - t))) +
                    (127.0f + (127.0f * sinf((float) (x + y) / 6.0f - t))) +
                    (127.0f + (127.0f * sinf(sqrtf(float(x*x + y*y)) / 4.0f - t)))
            ) / 4;

            // Write the texture pixel
            ptr[0] = vv;
            ptr[1] = vv;
            ptr[2] = vv;
            ptr[3] = vv;

            // To next pixel (our pixels are 4 bpp)
            ptr += 4;
        }

        // To next image row
        dst += textureRowPitch;
    }

    s_CurrentAPI->EndModifyTexture(textureHandle, width, height, textureRowPitch, textureDataPtr);
}


