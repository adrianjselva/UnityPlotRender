#ifndef UNITYPLOTRENDER_RENDERAPI_H
#define UNITYPLOTRENDER_RENDERAPI_H

#include "Unity/IUnityGraphics.h"

#include <cstddef>

struct IUnityInterfaces;


// Super-simple "graphics abstraction". This is nothing like how a proper platform abstraction layer would look like;
// all this does is a base interface for whatever our plugin sample needs. Which is only "draw some triangles"
// and "modify a texture" at this point.
//
// There are implementations of this base class for D3D9, D3D11, OpenGL etc.; see individual RenderAPI_* files.
class RenderAPI
{
public:
    virtual ~RenderAPI() = default;

    // Process general event like initialization, shutdown, device loss/reset etc.
    virtual void ProcessDeviceEvent(UnityGfxDeviceEventType type, IUnityInterfaces* interfaces) = 0;

    // Begin modifying texture data. You need to pass texture width/height too, since some graphics APIs
    // (e.g. OpenGL ES) do not have a good way to query that from the texture itself...
    //
    // Returns pointer into the data buffer to write into (or NULL on failure), and pitch in bytes of a single texture row.
    virtual void* BeginModifyTexture(void* textureHandle, int textureWidth, int textureHeight, int* outRowPitch) = 0;
    // End modifying texture data.
    virtual void EndModifyTexture(void* textureHandle, int textureWidth, int textureHeight, int rowPitch, void* dataPtr) = 0;
};


// Create a graphics API implementation instance for the given API type.
RenderAPI* CreateRenderAPI(UnityGfxRenderer apiType);

#endif //UNITYPLOTRENDER_RENDERAPI_H
