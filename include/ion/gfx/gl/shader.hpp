#pragma once

#include <ion/gfx/gl/resource.hpp>

#include <string>

#define GLSL(x) "#version 330\n" #x

namespace ion { namespace gfx { namespace gl
{
    class Shader : public Resource<Shader>
    {
    public:
        enum Type
        {
            Vertex,
            Fragment,
            Geometry
        };

    public:
        Shader(Type);
        Shader(Type, const std::string&);
        Shader(const Shader&);

        Shader& operator=(const Shader&);

        void source(const std::string&);
        void compile();

    private:
        void validate() const;

    public:
        static Shader fromFile(Type, const std::string&);
    };
}}}