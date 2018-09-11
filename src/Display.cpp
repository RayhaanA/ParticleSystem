#include "Display.h"
#include "Particle.h"
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <iostream>
#include <algorithm>

void print4x4(glm::mat4 m)
{
    std::cout << m[0][0] << " " << m[0][1] << " " << m[0][2] << " " << m[0][3] << "\n"
        << m[1][0] << " " << m[1][1] << " " << m[1][2] << " " << m[1][3] << "\n"
        << m[2][0] << " " << m[2][1] << " " << m[2][2] << " " << m[2][3] << "\n"
        << m[3][0] << " " << m[3][1] << " " << m[3][2] << " " << m[3][3] << "\n\n";
}

Display::Display()
{
    if (!glfwInit()) 
    {
       std::cerr << "Couldn't initialize glfw!" << std::endl;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(static_cast<int>(SCREEN_WIDTH), static_cast<int>(SCREEN_HEIGHT), "Particle System", nullptr, nullptr);

    if (!window) 
    {
        std::cerr << "Couldn't open GLFW window!" << std::endl;
        glfwTerminate();
    }
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSwapInterval(1); // 1 - Enables vsync, 0 - disables

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
    glClearColor(backgroundColour.r, backgroundColour.g, backgroundColour.b, backgroundColour.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.useShader();

    camera.speed() = 20.0f * static_cast<float>(elapsedTime);
   
    glm::mat4 view = camera.view();
    glm::mat4 projection = glm::perspective(glm::radians(camera.fov()), SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000.0f);

    // Sort by particle colour's distance to fix transparency
    std::sort(particles.begin(), particles.end(),
        [&camera](const Particle& lhs, const Particle& rhs)
        {
            return glm::length(camera.position() - lhs.position) > glm::length(camera.position() - rhs.position);
        });

    for (unsigned int i = 0; i < particles.size(); i++)
    {
        shader.set4fv("newColour", glm::vec4(particles[i].colour.r, particles[i].colour.g, particles[i].colour.b, particles[i].colour.a));

        glm::mat4 mvp = projection * view * particles[i].model;

        shader.setMatrix4fv("mvp", mvp);

        Particle::draw();

        particles[i].update(elapsedTime);
    }
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