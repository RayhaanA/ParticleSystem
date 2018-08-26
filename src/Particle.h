#pragma once
#include <glm.hpp>

class Particle
{
private:
    glm::vec3 position;
    glm::vec3 velocity;

public:
    Particle();
    ~Particle();
};