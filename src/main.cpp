#include "Display.h"
#include "InputManager.h"
#include <iostream>
#include <string>
#include <thread>

const unsigned int fps = 60;
void limitFPS(unsigned int FPS, double start);
void print4x4(glm::mat4 m)
{
    std::cout << m[0][0] << " " << m[0][1] << " " << m[0][2] << " " << m[0][3] << "\n"
        << m[1][0] << " " << m[1][1] << " " << m[1][2] << " " << m[1][3] << "\n"
        << m[2][0] << " " << m[2][1] << " " << m[2][2] << " " << m[2][3] << "\n"
        << m[3][0] << " " << m[3][1] << " " << m[3][2] << " " << m[3][3] << "\n\n";
}

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

    for (unsigned int i = 0; i < Particle::MAX_PARTICLES; i++)
    {
            particles.push_back(Particle(i));
            Particle::models.push_back(particles[i].model);
            Particle::colours.push_back(particles[i].colour.data);
    }

    glBindVertexArray(Particle::MeshInstance().vao);

    glGenBuffers(1, &Particle::modelsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, Particle::modelsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * Particle::models.size(), Particle::models.data(), GL_DYNAMIC_DRAW);
 
    for (unsigned int i = 0; i < Particle::models.size(); i++)
    {
        // set attribute pointers for matrix (4 times vec4)
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)(sizeof(glm::vec4)));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)(2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)(3 * sizeof(glm::vec4)));

        glVertexAttribDivisor(1, 1);
        glVertexAttribDivisor(2, 1);
        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
    }
    
    glGenBuffers(1, &Particle::coloursVBO);
    glBindBuffer(GL_ARRAY_BUFFER, Particle::coloursVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * Particle::colours.size(), Particle::colours.data(), GL_DYNAMIC_DRAW);

    for (unsigned int i = 0; i < Particle::colours.size(); i++)
    {
        // set attribute pointers for matrix (4 times vec4)
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);

        glVertexAttribDivisor(5, 1);
    }

    glBindVertexArray(0);

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