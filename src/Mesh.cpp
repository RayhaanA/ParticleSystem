#include "Mesh.h"
#include <iostream>

Mesh::Mesh()
{
    vao = vertexVBO = ebo = 0;
    vertices = {};
    indices = {};
    setupIndexingMethod();
}

Mesh::Mesh(std::vector<float> v, std::vector<unsigned int> i)
{
    vao = vertexVBO = ebo = 0;
    vertices = v;
    indices = i;
    setupInstancingMethod();
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vertexVBO);
    glDeleteBuffers(1, &ebo);
}

void Mesh::setupIndexingMethod()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vertexVBO);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Mesh::setupInstancingMethod()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vertexVBO);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Mesh::drawIndexed()
{
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(static_cast<GLsizei>(0));
}

void Mesh::drawInstanced(unsigned int numParticles)
{
    glBindVertexArray(vao);
    glDrawElementsInstanced(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0, numParticles);
    glBindVertexArray(static_cast<GLsizei>(0));
}