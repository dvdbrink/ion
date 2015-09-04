#pragma once

namespace ion { namespace gfx
{
    enum class BufferUsage
    {
        StreamCopy,
        StreamDraw,
        StreamRead,
        StaticCopy,
        StaticDraw,
        StaticRead,
        DynamicCopy,
        DynamicDraw,
        DynamicRead
    };
}}