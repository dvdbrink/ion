#pragma once

#include <ion/gfx/buffer_usage.hpp>
#include <ion/gfx/pixel_format.hpp>
#include <ion/gfx/primitive_type.hpp>
#include <ion/gfx/type.hpp>
#include <ion/gfx/gl/shader.hpp>

#include "extensions.h"

namespace ion { namespace gfx { namespace gl
{
    inline GLenum map(Format format)
    {
        switch (format)
        {
            case Format::BGR: return GL_BGR;
            case Format::BGRA: return GL_BGRA;
            case Format::Red: return GL_RED;
            case Format::RG: return GL_RG;
            case Format::RGB: return GL_RGB;
            case Format::RGBA: return GL_RGBA;
        }
    }

    inline GLenum map(PrimitiveType type)
    {
        switch (type)
        {
            case PrimitiveType::Triangles: return GL_TRIANGLES;
            case PrimitiveType::TriangleStrip: return GL_TRIANGLE_STRIP;
            case PrimitiveType::TriangleFan: return GL_TRIANGLE_FAN;
            case PrimitiveType::Points: return GL_POINTS;
            case PrimitiveType::Lines: return GL_LINES;
            case PrimitiveType::LineStrip: return GL_LINE_STRIP;
            case PrimitiveType::LineLoop: return GL_LINE_LOOP;
        }
    }

    inline GLenum map(Shader::Type type)
    {
        switch (type)
        {
            case Shader::Vertex: return GL_VERTEX_SHADER;
            case Shader::Fragment: return GL_FRAGMENT_SHADER;
            case Shader::Geometry: return GL_GEOMETRY_SHADER;
        }
    }

    inline GLenum map(BufferUsage usage)
    {
        switch (usage)
        {
            case BufferUsage::DynamicCopy: return GL_DYNAMIC_COPY;
            case BufferUsage::DynamicDraw: return GL_DYNAMIC_DRAW;
            case BufferUsage::DynamicRead: return GL_DYNAMIC_READ;
            case BufferUsage::StaticCopy: return GL_STATIC_COPY;
            case BufferUsage::StaticDraw: return GL_STATIC_DRAW;
            case BufferUsage::StaticRead: return GL_STATIC_READ;
            case BufferUsage::StreamCopy: return GL_STREAM_COPY;
            case BufferUsage::StreamDraw: return GL_STREAM_DRAW;
            case BufferUsage::StreamRead: return GL_STREAM_READ;
        }
    }

    inline GLenum map(Type type)
    {
        switch (type)
        {
            case Type::Float: return GL_FLOAT;
            case Type::UnsignedByte: return GL_UNSIGNED_BYTE;
            case Type::UnsignedShort: return GL_UNSIGNED_SHORT;
            case Type::UnsignedInt: return GL_UNSIGNED_INT;
        }
    }
}}}