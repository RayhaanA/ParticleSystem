#include "Particle.h"
#include <gtc\matrix_transform.hpp>
#include <glfw3.h>
#include <random>
#include <algorithm>

const unsigned int Particle::MAX_PARTICLES = 1000;

// For random particle parameters
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> dis(0.0f, 1.0f);
std::uniform_real_distribution<float> vel(-1.0f, 1.0f);

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
    velocity = { vel(gen), std::fabs(vel(gen)) + 0.3f, vel(gen) };
    life = std::max(dis(gen), 0.1f); // Make life random at the beginning so it starts more naturally
    fade = std::max(dis(gen), 0.1f) / 200.0f;
    gravity = { 0.0f, -0.006f, 0.0f };

    colour = Colour(dis(gen), dis(gen), dis(gen), 1.0f);

}

Particle::Particle(glm::vec3 pos, glm::vec3 vel, float fade, Colour colour) : position(pos), velocity(vel), fade(fade), colour(colour)
{
    speed = SLOW;
    life = 1.0f;
    gravity = { 0.0f, -0.006f, 0.0f };
}

void Particle::update(double elapsedTime)
{
    velocity += gravity;
    position += speed * velocity;
   
    life -= fade;
    if (life <= 0.0)
    {
        position = { 0.0f, 0.0f, 0.0f };
        velocity = { vel(gen), std::fabs(vel(gen)) + 0.3f, vel(gen) };
        life = 1.0;
    }
    colour.a = life;

    model = glm::mat4();
    model = glm::translate(model, position);
    //model = glm::rotate(model, static_cast<float>(glfwGetTime()), { 0.4f, 0.8f, 0.2f });
}

void Particle::draw()
{
    MeshInstance().draw();
}