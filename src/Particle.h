#pragma once
#include <glm.hpp>
#include <vector>

static float PARTICLE_SPEED = 0.1f;
static glm::vec3 PARTICLE_DIRECTION = { 0.0f, 0.0f, 0.0f };
const unsigned int MAX_PARTICLES = 100;

struct Particle
{
    glm::vec3 position;
    glm::vec3 velocity;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    Particle();
    Particle(glm::vec3 pos, glm::vec3 vel);
    ~Particle();

    void update();
};