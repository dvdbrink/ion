#include "context_impl.hpp"

#include <ion/platform.hpp>

#if defined(ION_PLATFORM_LINUX)
    #include "glx/context_impl.hpp"
#elif defined(ION_PLATFORM_WINDOWS)
    #include "wgl/context_impl.hpp"
#endif

namespace ion { namespace wnd
{
    std::unique_ptr<ContextImpl> ContextImpl::create(const WindowHandle& handle)
    {
        #if defined(ION_PLATFORM_LINUX)
            return std::make_unique<glx::GLXContextImpl>(handle);
        #elif defined(ION_PLATFORM_WINDOWS)
            return std::make_unique<wgl::WGLContextImpl>(handle);
        #endif
    }

    ContextImpl::ContextImpl(const WindowHandle& windowHandle) : _handle(windowHandle) {}

    ContextImpl::~ContextImpl() {}
}}