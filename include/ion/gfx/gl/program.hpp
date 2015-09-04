#pragma once

#include <ion/gfx/color.hpp>
#include <ion/gfx/gl/resource.hpp>
#include <ion/math/matrix.hpp>

#include <string>

namespace ion { namespace gfx { namespace gl
{
    class Shader;

    class Program : public Resource<Program>
    {
    public:
        Program();
        Program(const Shader&, const Shader&);
        Program(const Shader&, const Shader&, const Shader&);
        Program(const Program&);

        Program& operator=(const Program&);

        void attach(const Shader&);
        void detach(const Shader&);

        void link();
        void use();

        unsigned int attribute(const std::string&) const;
        unsigned int uniform(const std::string&) const;

        void uniform(const std::string&, const math::Matrix4f&);
        void uniform(const std::string&, const Color&);
        void uniform(const std::string&, const int);
        void uniform(const std::string&, const float);

    private:
        void validate() const;
    };
}}}