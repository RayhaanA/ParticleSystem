#include "Particle.h"

Particle::Particle()
{
    position = { 0.0f, 0.0f, 0.0f };
    velocity = { 1.0f, 0.0f, 0.0f };

    vertices = { 0.5f, 0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                -0.5f, -0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f };

    indices = { 0, 1, 3,
                1, 2, 3 }; 
}

Particle::Particle(glm::vec3 pos, glm::vec3 vel) : position(pos), velocity(vel)
{
    vertices = { 0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f };

    indices = { 0, 1, 3,
        1, 2, 3 };
}

Particle::~Particle()
{

}

void Particle::update()
{
    velocity = { PARTICLE_SPEED, 0.0f, 0.0f };
    position += velocity;
}