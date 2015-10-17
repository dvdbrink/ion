#include <ion/gfx/clear.hpp>

#include "error.hpp"
#include "extensions.h"

namespace ion { namespace gfx
{
    void clear_color(Color color)
    {
        check_error(glClearColor(color.r, color.g, color.b, color.a));
    }

    void clear()
    {
        check_error(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
    }
}}
