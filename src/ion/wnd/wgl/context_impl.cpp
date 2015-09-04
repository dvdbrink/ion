#include "context_impl.hpp"

#include <ion/log/out.hpp>

#include "extensions.h"

#include <windows.h>

namespace ion { namespace wnd { namespace wgl
{
    WGLContextImpl::WGLContextImpl(const WindowHandle& windowHandle) : ContextImpl(windowHandle)
    {
        deviceContext = GetDC(windowHandle.hwnd);

        PIXELFORMATDESCRIPTOR pfd;
        memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
        pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 32;
        pfd.cDepthBits = 32;
        pfd.iLayerType = PFD_MAIN_PLANE;

        int nPixelFormat = ChoosePixelFormat(deviceContext, &pfd);
        if (nPixelFormat == 0) {
            MessageBox(NULL, "ChoosePixelFormat Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        }

        int bResult = SetPixelFormat(deviceContext, nPixelFormat, &pfd);
        if (!bResult) {
            MessageBox(NULL, "SetPixelFormat Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        }

        HGLRC tempContext = wglCreateContext(deviceContext);
        wglMakeCurrent(deviceContext, tempContext);

        int attributes[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
            WGL_CONTEXT_MINOR_VERSION_ARB, 3,
            WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
            0
        };

        renderContext = wglCreateContextAttribsARB(deviceContext, NULL, attributes);
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(tempContext);
        wglMakeCurrent(deviceContext, renderContext);
    }

    WGLContextImpl::~WGLContextImpl()
    {
        wglMakeCurrent(deviceContext, 0);
        wglDeleteContext(renderContext);
        ReleaseDC(_handle.hwnd, deviceContext);
    }

    void WGLContextImpl::swap_buffers()
    {
        SwapBuffers(deviceContext);
    }

    void WGLContextImpl::vertical_sync(bool interval)
    {
        wglSwapIntervalEXT(interval);
    }
}}}