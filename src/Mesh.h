#pragma once
#include "Shader.h"
#include <vector>

class Mesh
{
private:
    GLuint vertexVBO;
    GLuint ebo;
    void setupIndexingMethod();
    void setupInstancingMethod();
public:
    GLuint vao;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    // No normals or textures yet

    Mesh();
    Mesh(std::vector<float> v, std::vector<unsigned int> i);
    ~Mesh();

    void drawIndexed();
    void drawInstanced(unsigned int numParticles);
};