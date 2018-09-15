#pragma once
#include "Mesh.h"
#include <glm.hpp>
#include <vector>

struct Colour
{
    glm::vec4 data;

    Colour()
    {
        data = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }

    Colour(float r, float g, float b, float a) : data(r, g, b, a)
    {}


    Colour& Colour::operator=(const Colour &rhs)
    {
        if (this != &rhs)
        {
            data = rhs.data;
        }
        return *this;
    }
};


struct Particle
{
    static const unsigned int MAX_PARTICLES;
    static GLuint modelsVBO;
    static GLuint coloursVBO;
    static std::vector<glm::mat4> models;
    static std::vector<glm::vec4> colours;

    static Mesh& MeshInstance(); // Each particle will have the same mesh data

    const float SLOW = 0.01f;
    const float NORMAL = 0.1f;
    const float FAST = 1.0f;

    unsigned int index; // To keep reference to its position in the main model matrix array

    float speed;
    float life;
    float fade;
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 gravity;
    glm::mat4 model;

    Colour colour;

    Particle();
    Particle(unsigned int i);
    Particle(glm::vec3 pos, glm::vec3 vel, float fade, Colour colour);
    ~Particle() = default;

    void update(double elapsedTime);

    static void drawIndexed();
    static void drawInstanced();

    Particle& Particle::operator=(const Particle &rhs)
    {
        if (this != &rhs)
        {
            speed = rhs.speed;
            life = rhs.life;
            fade = rhs.fade;
            position = rhs.position;
            velocity = rhs.velocity;
            gravity = rhs.gravity;
            model = rhs.model;
            colour = rhs.colour;
        }
        return *this;
    }
};