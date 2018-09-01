#pragma once
#include "Shader.h"
#include <vector>

class Mesh
{
private:
    GLuint vbo;
    GLuint ebo;
    void setup();
public:
    GLuint vao;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    // No normals or textures yet

    Mesh();
    Mesh(std::vector<float> v, std::vector<unsigned int> i);
    ~Mesh();

    void draw();
};