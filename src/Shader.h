#pragma once
#include <fstream>
#include <glew.h>
#include <glm.hpp>

class Shader
{
private:
    GLuint program;

public:
    Shader(const std::string& vertexShader, const std::string& fragmentShader);
    ~Shader();
    void useShader();
    GLuint getProgram() const;

    // Uniform utility functions
    void setMatrix4fv(const char* name, glm::mat4 value);
    void set4fv(const char* name, glm::vec4 value);
};

