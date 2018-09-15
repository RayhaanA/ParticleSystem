#include "Display.h"
#include "Particle.h"
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <iostream>
#include <algorithm>

/*void print4x4(glm::mat4 m)
{
    std::cout << m[0][0] << " " << m[0][1] << " " << m[0][2] << " " << m[0][3] << "\n"
        << m[1][0] << " " << m[1][1] << " " << m[1][2] << " " << m[1][3] << "\n"
        << m[2][0] << " " << m[2][1] << " " << m[2][2] << " " << m[2][3] << "\n"
        << m[3][0] << " " << m[3][1] << " " << m[3][2] << " " << m[3][3] << "\n\n";
}*/

Display::Display()
{
    if (!glfwInit()) 
    {
       std::cerr << "Couldn't initialize glfw!" << std::endl;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(static_cast<int>(SCREEN_WIDTH), static_cast<int>(SCREEN_HEIGHT), "Particle System", glfwGetPrimaryMonitor(), nullptr);

    if (!window) 
    {
        std::cerr << "Couldn't open GLFW window!" << std::endl;
        glfwTerminate();
    }
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwMakeContextCurrent(window);
        
    glewExperimental = GL_TRUE;
    glewInit();

    // Depth buffer enable
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Colour blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Interpolate

    // Wireframe mode: GL_LINE, Normal: GL_FILL
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    backgroundColour = Colour(0.0f, 0.0f, 0.0f, 1.0f);
}

Display::~Display()
{
    glfwTerminate();
}

GLFWwindow* Display::getWindow() const
{
    return window;
}

void Display::update(Shader shader, Camera& camera, double elapsedTime, std::vector<Particle>& particles)
{
    glClearColor(backgroundColour.data.x, backgroundColour.data.y, backgroundColour.data.z, backgroundColour.data.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.useShader();

    camera.speed() = 20.0f * static_cast<float>(elapsedTime);
   
    glm::mat4 view = camera.view();
    glm::mat4 projection = glm::perspective(glm::radians(camera.fov()), SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000.0f);

    shader.setMatrix4fv("view", view);
    shader.setMatrix4fv("projection", projection);

    // Sort by particle colour's distance to fix transparency
    std::sort(particles.begin(), particles.end(),
        [&camera](const Particle& lhs, const Particle& rhs)
        {
            return glm::length(camera.position() - lhs.position) > glm::length(camera.position() - rhs.position);
        });

    for (unsigned int i = 0; i < particles.size(); i++)
    {
        //shader.set4fv("newColour", glm::vec4(particles[i].colour.r, particles[i].colour.g, particles[i].colour.b, particles[i].colour.a));

        //shader.setMatrix4fv("m", particles[i].model);

        particles[i].update(elapsedTime);
    }

    glBindVertexArray(Particle::MeshInstance().vao);

    glBindBuffer(GL_ARRAY_BUFFER, Particle::modelsVBO);
    glBufferData(GL_ARRAY_BUFFER, Particle::models.size() * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, Particle::models.size() * sizeof(glm::mat4), Particle::models.data());

    glBindBuffer(GL_ARRAY_BUFFER, Particle::coloursVBO);
    glBufferData(GL_ARRAY_BUFFER, Particle::colours.size() * sizeof(glm::vec4), nullptr, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, Particle::colours.size() * sizeof(glm::vec4), Particle::colours.data());
    glBindVertexArray(static_cast<GLsizei>(0));

    Particle::drawInstanced();
}

void Display::render()
{
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void Display::setBackgroundColour(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
{
    backgroundColour = { r, g, b, a };
}