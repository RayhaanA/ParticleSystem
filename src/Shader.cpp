#include "Shader.h"
#include <string>
#include <iostream>
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

    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
}


Shader::~Shader()
{
    glDeleteProgram(program);
}

void Shader::useShader()
{
    glUseProgram(program);
}

GLuint Shader::getProgram()
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
