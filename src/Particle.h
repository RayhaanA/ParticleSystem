#pragma once
#include <glm.hpp>
#include <vector>



struct Particle
{
    static const unsigned int MAX_PARTICLES;
    const float DEFAULT_PARTICLE_SPEED = 20.0f;

    float speed;
    glm::vec3 position;
    glm::vec3 velocity;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    Particle();
    Particle(glm::vec3 pos, glm::vec3 vel);
    ~Particle();

    void update(double elapsedTime);
};