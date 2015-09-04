#include <ion/gfx/gl/program.hpp>

#include <ion/log/out.hpp>
#include <ion/gfx/gl/shader.hpp>

#include "error.hpp"
#include "extensions.h"

namespace ion { namespace gfx { namespace gl
{
    Program::Program() : Resource(glCreateProgram(), glDeleteProgram) {}

    Program::Program(const Shader& vertex, const Shader& fragment) : Program()
    {
        attach(vertex);
        attach(fragment);
        link();
    }

    Program::Program(const Shader& vertex, const Shader& fragment, const Shader& geometry) : Program()
    {
        attach(vertex);
        attach(fragment);
        attach(geometry);
        link();
    }

    Program::Program(const Program& copy) : Resource(copy) {}

    Program& Program::operator=(const Program& copy)
    {
        Resource::operator=(copy);
        return *this;
    }

    void Program::attach(const Shader& shader)
    {
        check_error(glAttachShader(id(), shader.id()));
    }

    void Program::detach(const Shader& shader)
    {
        check_error(glDetachShader(id(), shader.id()));
    }

    void Program::link()
    {
        check_error(glLinkProgram(id()));
        validate();
    }

    void Program::use()
    {
        check_error(glUseProgram(id()));
    }

    unsigned int Program::attribute(const std::string& name) const
    {
        auto attribute = glGetAttribLocation(id(), name.c_str());
        if (attribute == -1)
        {
            log::out<log::Warn>() << "Attribute " << name << " not found." << log::Endl;
        }
        return static_cast<unsigned int>(attribute);
    }

    unsigned int Program::uniform(const std::string& name) const
    {
        auto uniform = glGetUniformLocation(id(), name.c_str());
        if (uniform == -1)
        {
            log::out<log::Warn>() << "Uniform " << name << " not found." << log::Endl;
        }
        return static_cast<unsigned int>(uniform);
    }

    void Program::uniform(const std::string& name, const math::Matrix4f& mat)
    {
        check_error(glUniformMatrix4fv(uniform(name), 1, false, &mat[0][0]));
    }

    void Program::uniform(const std::string& name, const Color& color)
    {
        check_error(glUniform4f(uniform(name), color.r, color.g, color.b, color.a));
    }

    void Program::uniform(const std::string& name, const int i)
    {
        check_error(glUniform1i(uniform(name), i));
    }

    void Program::uniform(const std::string& name, const float f)
    {
        check_error(glUniform1f(uniform(name), f));
    }

    void Program::validate() const
    {
        GLint linked;
        check_error(glGetProgramiv(id(), GL_LINK_STATUS, &linked));
        if (!linked)
        {
            GLint infoLogLength;
            check_error(glGetProgramiv(id(), GL_INFO_LOG_LENGTH, &infoLogLength));
            log::out<log::Error>() << "Program (" << id() << ") linking failed.";
            if (infoLogLength > 0)
            {
                std::string infoLog(infoLogLength, ' ');
                check_error(glGetProgramInfoLog(id(), infoLogLength, &infoLogLength, &infoLog.front()));
                log::out<log::Error>() << " Reason: " << infoLog;
            }
            else
            {
                log::out<log::Error>() << log::Endl;
            }
        }

        GLint validated;
        check_error(glValidateProgram(id()));
        check_error(glGetProgramiv(id(), GL_VALIDATE_STATUS, &validated));
        if (!validated)
        {
            log::out<log::Error>() << "Error validating program " << id() << log::Endl;
        }
    }
}}}