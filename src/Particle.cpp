#include "Particle.h"
#include <gtc\matrix_transform.hpp>
#include <glfw3.h>
#include <random>

const unsigned int Particle::MAX_PARTICLES = 100;
std::random_device rd; // For random particle parameters
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0.0, 1.0);

Mesh& Particle::MeshInstance()
{
    static Mesh mesh({ 0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f },
    { 0, 1, 3, 1, 2, 3 });

    return mesh;
}

Particle::Particle()
{
    speed = NORMAL;
    position = { 0.0f, 0.0f, 0.0f };
    velocity = { 1.0f, 0.0f, 0.0f };
    life = 1.0f;
    fade = 0.005f;
    gravity = { 0.0f, 0.0f, 0.0f };

    colour = Colour();
}

Particle::Particle(glm::vec3 pos, glm::vec3 vel) : position(pos), velocity(vel)
{
    speed = SLOW;
    life = 1.0f;
    fade = static_cast<float>(dis(gen) / 300.0);
    gravity = { 0.0f, 0.0f, 0.0f };

    colour = Colour(static_cast<float>(dis(gen)), static_cast<float>(dis(gen)), static_cast<float>(dis(gen)), life);
}

void Particle::update(double elapsedTime)
{
    position += speed * velocity + gravity;
   
    life -= fade;
    if (life <= 0.0)
    {
        life = 1.0;
    }
    colour.a = life;

    model = glm::mat4();
    model = glm::translate(model, position);
    model = glm::rotate(model, static_cast<float>(glfwGetTime()), { 0.4f, 0.8f, 0.2f });
}

void Particle::draw()
{
    MeshInstance().draw();
}