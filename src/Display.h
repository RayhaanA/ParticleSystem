#pragma once
#include "Shader.h"
#include "Camera.h"
#include "Particle.h"
#include <glfw3.h>
#include <glm.hpp>
#include <vector>

class Display
{
private:
    const float SCREEN_HEIGHT = 720.f;
    const float SCREEN_WIDTH = 1280.f;
    GLFWwindow* window;
    struct BackgroundColour
    {
        GLclampf r = 0.0f;
        GLclampf g = 0.0f;
        GLclampf b = 0.0f;
        GLclampf a = 1.0f;
    } backgroundColour;

public:
    Display();
    ~Display();
    GLFWwindow* getWindow() const;
    void update(Shader shader, Camera& camera, double elapsedTime, std::vector<Particle>& particles);
    void render();
    void setBackgroundColour(GLclampf r, GLclampf g, GLclampf b, GLclampf a);
};
