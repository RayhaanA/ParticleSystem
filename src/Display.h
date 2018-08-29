#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <vector>
#include "Shader.h"
#include "Camera.h"
#include "Particle.h"

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
    void update(GLuint vao, Shader shader, Camera& camera, std::vector<Particle>& particles);
    // Takes a vao and shader for drawing
    void render();
    void setBackgroundColour(GLclampf r, GLclampf g, GLclampf b, GLclampf a);
};
