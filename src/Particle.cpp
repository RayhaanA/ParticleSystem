#include "Particle.h"

const unsigned int Particle::MAX_PARTICLES = 100;

Particle::Particle()
{
    speed = DEFAULT_PARTICLE_SPEED;
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
    speed = DEFAULT_PARTICLE_SPEED;
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

void Particle::update(double elapsedTime)
{
    speed = DEFAULT_PARTICLE_SPEED * (0.2f + static_cast<float>(+ elapsedTime));
    velocity = { speed * static_cast<float>(elapsedTime), 0.0f, 0.0f };
    //position += velocity;
}