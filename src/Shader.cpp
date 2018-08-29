#include "Shader.h"
#include <string>
#include <iostream>
#include <vector>
#include <gtc\type_ptr.hpp>

Shader::Shader(const std::string &vertexShader, const std::string &fragmentShader)
{
    std::ifstream vsFile(vertexShader);
    std::ifstream fsFile(fragmentShader);

    if (!vsFile) 
    {
        std::cerr << "Couldn't open vertex shader file(s)!" << "\n";
    }

    if (!fsFile)
    {
        std::cerr << "Couldn't open fragment shader file(s)!" << "\n";
    }

    std::string vsContent{ std::istreambuf_iterator<char>{ vsFile }, {} };
    std::string fsContent{ std::istreambuf_iterator<char>{ fsFile }, {} };

    std::cout << "Vertex Shader:\n" << vsContent << "\n\n";
    std::cout << "Fragment Shader:\n" << fsContent << "\n\n";

    const char *vsContentToChar = vsContent.c_str();
    const char *fsContentToChar = fsContent.c_str();

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsContentToChar, nullptr);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsContentToChar, nullptr);
    glCompileShader(fs);

    GLint isVsCompiled = 0;
    GLint isFsCompiled = 0;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &isVsCompiled);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &isFsCompiled);

    if (isVsCompiled == GL_FALSE || isFsCompiled == GL_FALSE)
    {
        GLint maxLengthVs = 0;
        GLint maxLengthFs = 0;
        glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxLengthVs);
        glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &maxLengthFs);

        // The maxLength includes the NULL character
        std::vector<GLchar> errorLogVs(maxLengthVs);
        std::vector<GLchar> errorLogFs(maxLengthFs);

        glGetShaderInfoLog(vs, maxLengthVs, &maxLengthVs, &errorLogVs[0]);
        glGetShaderInfoLog(fs, maxLengthFs, &maxLengthFs, &errorLogFs[0]);

        for (const auto& i : errorLogVs)
        {
            std::cerr << i;
        }

        for (const auto& i : errorLogFs)
        {
            std::cerr << i;
        }

        glDeleteShader(vs);
        glDeleteShader(fs);
        return;
    }

    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    // Clean up unneccesary resources
    glDetachShader(program, vs);
    glDetachShader(program, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);
}


Shader::~Shader()
{
    glDeleteProgram(program);
}

void Shader::useShader()
{
    glUseProgram(program);
}

GLuint Shader::getProgram() const
{
    return program;
}

void Shader::setMatrix4fv(const char* name, glm::mat4 value)
{
    int location = glGetUniformLocation(program, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::set4fv(const char* name, glm::vec4 value)
{
    int location = glGetUniformLocation(program, name);
    glUniform4f(location, value[0], value[1], value[2], value[3]);
}
