#include "RenderAPI.h"
#include "PlatformBase.h"

//#if SUPPORT_OPENGL_UNIFIED
//#include <assert.h>
//#if UNITY_IOS || UNITY_TVOS
//#	include <OpenGLES/ES2/gl.h>
//#elif UNITY_ANDROID || UNITY_WEBGL || UNITY_EMBEDDED_LINUX
//#	include <GLES2/gl2.h>
//#elif UNITY_OSX
//#	include <OpenGL/gl3.h>
//#elif UNITY_WIN
//// On Windows, use gl3w to initialize and load OpenGL Core functions. In principle any other
//// library (like GLEW, GLFW etc.) can be used; here we use gl3w since it's simple and
//// straightforward.
//#	include "gl3w/gl3w.h"
//#elif UNITY_LINUX || UNITY_EMBEDDED_LINUX_GL
//#	define GL_GLEXT_PROTOTYPES
//#	include <GL/gl.h>
//#else
//#	error Unknown platform
//#endif
//
//#endif

#include <GL/gl.h>

class RenderAPI_OpenGLCoreES : public RenderAPI
{
public:
	explicit RenderAPI_OpenGLCoreES(UnityGfxRenderer apiType);
	~RenderAPI_OpenGLCoreES() override = default;

	void ProcessDeviceEvent(UnityGfxDeviceEventType type, IUnityInterfaces* interfaces) override;

	virtual bool GetUsesReverseZ() { return false; }

	void* BeginModifyTexture(void* textureHandle, int textureWidth, int textureHeight, int* outRowPitch) override;
	void EndModifyTexture(void* textureHandle, int textureWidth, int textureHeight, int rowPitch, void* dataPtr) override;

private:
	void CreateResources();

private:
	UnityGfxRenderer m_APIType;
};

RenderAPI* CreateRenderAPI_OpenGLCoreES(UnityGfxRenderer apiType) {
    return new RenderAPI_OpenGLCoreES(apiType);
}

RenderAPI_OpenGLCoreES::RenderAPI_OpenGLCoreES(UnityGfxRenderer apiType)
        : m_APIType(apiType) {}

void RenderAPI_OpenGLCoreES::CreateResources() {

}

void RenderAPI_OpenGLCoreES::ProcessDeviceEvent(UnityGfxDeviceEventType type, IUnityInterfaces* interfaces)
{
    if (type == kUnityGfxDeviceEventInitialize)
    {
        CreateResources();
    }
    else if (type == kUnityGfxDeviceEventShutdown)
    {
        //@TODO: release resources
    }
}

void* RenderAPI_OpenGLCoreES::BeginModifyTexture(void* textureHandle, int textureWidth, int textureHeight, int* outRowPitch)
{
    const int rowPitch = textureWidth * 4;
    // Just allocate a system memory buffer here for simplicity
    auto* data = new unsigned char[rowPitch * textureHeight];
    *outRowPitch = rowPitch;
    return data;
}


void RenderAPI_OpenGLCoreES::EndModifyTexture(void* textureHandle, int textureWidth, int textureHeight, int rowPitch, void* dataPtr)
{
    auto gltex = (GLuint)(size_t)(textureHandle);
    // Update texture data, and free the memory buffer
    glBindTexture(GL_TEXTURE_2D, gltex);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, textureWidth, textureHeight, GL_RGBA, GL_UNSIGNED_BYTE, dataPtr);
    delete[](unsigned char*)dataPtr;
}