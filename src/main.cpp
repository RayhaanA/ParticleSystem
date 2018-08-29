#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <string>
#include "Shader.h"
#include "Display.h"
#include "Camera.h"
#include "InputManager.h"
#include "Particle.h"

int main()
{
    std::ios_base::sync_with_stdio(false);

    Display display;

    Shader shader("./shaders/vertex_shader.vert", "./shaders/fragment_shader.frag");

    Camera camera;

    std::string renderer(reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    std::string version(reinterpret_cast<const char*>(glGetString(GL_VERSION)));

    std::cout << "Renderer: " << renderer << "\n";
    std::cout << "Version: " << version << "\n";

    std::vector<Particle> particles;
    
    for (unsigned int i = 0; i < MAX_PARTICLES / 10; i++)
    {
        for (unsigned int j = 0; j < MAX_PARTICLES / 10; j++)
        {
            particles.push_back(Particle({ -10.0f + i * 2.0f, -10.0f + j * 2.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }));
        }
    }

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);

    GLuint ebo = 0;
    glGenBuffers(1, &ebo);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, particles[0].vertices.size() * sizeof(particles[0].vertices[0]), particles[0].vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, particles[0].indices.size() * sizeof(particles[0].indices[0]), particles[0].indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    display.setBackgroundColour(0.055f, 0.067f, 0.067f, 1.0f);

    double deltaTime = 0.0f;
    double lastFrame = glfwGetTime();
    // int numFrames = 0;
    double oldXPos = 0;
    double oldYPos = 0;
    double xPos = 400;
    double yPos = 300;

    while (!glfwWindowShouldClose(display.getWindow())) 
    {
        double currentFrame = glfwGetTime();

        deltaTime = currentFrame - lastFrame;
        
        glfwGetCursorPos(display.getWindow(), &xPos, &yPos);

        camera.speed() = 20.0f * static_cast<float>(deltaTime);
        PARTICLE_SPEED = 0.1f * static_cast<float>(deltaTime);

        InputManager::processKeyPress(display.getWindow(), camera);
        InputManager::processMouseMove(display.getWindow(), xPos, yPos, oldXPos, oldYPos, camera);

        oldXPos = xPos;
        oldYPos = yPos;

        display.update(vao, shader, camera, particles);
        display.render();

        lastFrame = currentFrame;
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    return 0;
}