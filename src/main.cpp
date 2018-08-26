#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <string>
#include "Shader.h"
#include "Display.h"
#include "Camera.h"
#include "InputManager.h"


int main()
{
    //std::ios_base::sync_with_stdio(false);

    Display display;

    Shader shader("./shaders/vertex_shader.vert", "./shaders/fragment_shader.frag");

    Camera camera;

    std::string renderer(reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    std::string version(reinterpret_cast<const char*>(glGetString(GL_VERSION)));

    std::cout << "Renderer: " << renderer << "\n";
    std::cout << "Version: " << version << "\n";

    GLfloat vertices[] = { -6.0f, 6.0f, -6.0f,
        -6.0f, -6.0, -6.0f,
        6.0f, -6.0f, -6.0f,
        -6.0f, 6.0f, -6.0f,
        6.0f, 6.0f, -6.0f,
        6.0f, -6.0f, -6.0f
    };

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    display.setBackgroundColour(0.7f, 0.3f, 1.0f, 1.0f);

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

        camera.speed() = 20.0f * deltaTime;
        
        InputManager::processKeyPress(display.getWindow(), camera);
        InputManager::processMouseMove(display.getWindow(), xPos, yPos, oldXPos, oldYPos, camera);

        oldXPos = xPos;
        oldYPos = yPos;

        display.update(vao, shader, camera);
        display.render();

        lastFrame = currentFrame;
    }

    return 0;
}