#include "context_impl.hpp"

#include "extensions.h"

namespace ion { namespace wnd { namespace glx
{
    GLXContextImpl::GLXContextImpl(const WindowHandle& windowHandle) : ContextImpl(windowHandle)
    {
        XWindowAttributes window_attributes;
        XGetWindowAttributes(windowHandle.display, windowHandle.window, &window_attributes);

        XVisualInfo visual_info;
        visual_info.depth = window_attributes.depth;
        visual_info.visualid = XVisualIDFromVisual(window_attributes.visual);
        visual_info.screen = windowHandle.screen;

        int nb_visuals = 0;
        XVisualInfo* visuals = XGetVisualInfo(windowHandle.display, VisualDepthMask | VisualIDMask | VisualScreenMask, &visual_info, &nb_visuals);

        GLXContext temp_context = glXCreateContext(windowHandle.display, visuals, NULL, GL_FALSE);
        glXMakeCurrent(windowHandle.display, windowHandle.window, temp_context);
        glXDestroyContext(windowHandle.display, temp_context);

        int nb_configs = 0;
        GLXFBConfig* configs = glXChooseFBConfig(windowHandle.display, windowHandle.screen, NULL, &nb_configs);

        int context_attributes[] = {
            GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
            GLX_CONTEXT_MINOR_VERSION_ARB, 3,
            GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };
        context = glXCreateContextAttribsARB(windowHandle.display, configs[0], NULL, GL_TRUE, context_attributes);
        glXMakeCurrent(windowHandle.display, windowHandle.window, context);

        Colormap color_map = XCreateColormap(windowHandle.display, RootWindow(windowHandle.display, windowHandle.screen), visuals[0].visual, AllocNone);
        XSetWindowColormap(windowHandle.display, windowHandle.window, color_map);
        XFree(visuals);
    }

    GLXContextImpl::~GLXContextImpl()
    {
        glXMakeCurrent(_handle.display, 0, 0);
        glXDestroyContext(_handle.display, context);
    }

    void GLXContextImpl::swap_buffers()
    {
        glXSwapBuffers(_handle.display, _handle.window);
    }

    void GLXContextImpl::vertical_sync(bool interval)
    {
        glXSwapIntervalEXT(_handle.display, _handle.window, interval);
    }
}}}