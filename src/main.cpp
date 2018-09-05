#include "Display.h"
#include "InputManager.h"
#include <iostream>
#include <string>
#include <thread>

const unsigned int fps = 200;
void limitFPS(unsigned int FPS, double start);

int main()
{
    std::ios_base::sync_with_stdio(false); // Faster cout for debugging

    Display display;

    Camera camera;

    Shader shader("./shaders/vertex_shader.vert", "./shaders/fragment_shader.frag");

    std::string renderer(reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    std::string version(reinterpret_cast<const char*>(glGetString(GL_VERSION)));

    std::cout << "Renderer: " << renderer << "\n";
    std::cout << "Version: " << version << "\n";

    std::vector<Particle> particles;
    
    for (unsigned int i = 0; i < Particle::MAX_PARTICLES / 10; i++)
    {
        for (unsigned int j = 0; j < Particle::MAX_PARTICLES / 10; j++)
        {
            particles.push_back(Particle({ -10.0f + i * 2.0f, -10.0f + j * 2.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }));
        }
    }

    display.setBackgroundColour(0.055f, 0.067f, 0.067f, 1.0f);

    double deltaTime = 0.0f;
    double lastFrame = glfwGetTime();
    double oldXPos = 0;
    double oldYPos = 0;
    double xPos = 400;
    double yPos = 300;
    // int numFrames = 0;

    while (!glfwWindowShouldClose(display.getWindow())) 
    {
        double currentFrame = glfwGetTime();

        deltaTime = currentFrame - lastFrame;
        
        camera.speed() = 20.0f * static_cast<float>(deltaTime);

        glfwGetCursorPos(display.getWindow(), &xPos, &yPos);

        InputManager::processKeyPress(display.getWindow(), camera);
        InputManager::processMouseMove(display.getWindow(), xPos, yPos, oldXPos, oldYPos, camera);

        oldXPos = xPos;
        oldYPos = yPos;

        display.update(shader, camera, deltaTime, particles);
        display.render();

        lastFrame = currentFrame;

        //limitFPS(fps, currentFrame);
    }

    return 0;
}

// Thread sleeps so that only a max of 'FPS' frames are drawn per second
void limitFPS(unsigned int FPS, double start)
{
    auto timeToSleep = static_cast<std::chrono::milliseconds>(static_cast<long long>((1000 / FPS - (glfwGetTime() * 1000 - start * 1000))));
    std::this_thread::sleep_for(timeToSleep);
}