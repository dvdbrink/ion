#include <ion/gfx/gl/shader.hpp>

#include <ion/log/out.hpp>

#include "error.hpp"
#include "extensions.h"
#include "map.hpp"

#include <fstream>

namespace ion { namespace gfx { namespace gl
{
    Shader::Shader(Type type) : Resource(glCreateShader(map(type)), glDeleteShader) {}

    Shader::Shader(Type type, const std::string& code) : Shader(type)
    {
        source(code);
        compile();
    }

    Shader::Shader(const Shader& copy) : Resource(copy) {}

    Shader& Shader::operator=(const Shader& copy)
    {
        Resource::operator=(copy);
        return *this;
    }

    void Shader::source(const std::string& code)
    {
        const char* c = code.c_str();
        check_error(glShaderSource(id(), 1, &c, 0));
    }

    void Shader::compile()
    {
        check_error(glCompileShader(id()));
        validate();
    }

    void Shader::validate() const
    {
        GLint compiled;
        check_error(glGetShaderiv(id(), GL_COMPILE_STATUS, &compiled));
        if (!compiled)
        {
            log::out<log::Error>() << "Shader (" << id() << ") compilation failed.";
            GLint infoLogLength;
            check_error(glGetShaderiv(id(), GL_INFO_LOG_LENGTH, &infoLogLength));
            if (infoLogLength)
            {
                std::string infoLog(infoLogLength, ' ');
                check_error(glGetShaderInfoLog(id(), infoLogLength, &infoLogLength, &infoLog.front()));
                log::out<log::Error>() << " Reason: " << infoLog;
            }
            else
            {
                log::out<log::Error>() << log::Endl;
            }
        }
    }

    Shader Shader::fromFile(Type type, const std::string& fileName)
    {
        std::string code, line;
        std::ifstream in(fileName);
        if (in.is_open())
        {
            while (!in.eof())
            {
                std::getline(in, line);
                code.append(line);
                code.append("\n");
            }
            in.close();
        }
        return {type, code};
    }
}}}