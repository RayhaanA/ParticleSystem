#pragma once
#include "Mesh.h"
#include <glm.hpp>
#include <vector>

struct Particle
{
    static const unsigned int MAX_PARTICLES;
    
    static Mesh& MeshInstance(); // Each particle will have the same mesh data

    const float DEFAULT_PARTICLE_SPEED = 20.0f;

    float speed;
    glm::vec3 position;
    glm::vec3 velocity;
    
    Particle();
    Particle(glm::vec3 pos, glm::vec3 vel);
    ~Particle() = default;

    void update(double elapsedTime);

    static void draw();
};