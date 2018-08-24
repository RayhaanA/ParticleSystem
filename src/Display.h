#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include "Shader.h"
#include "Camera.h"

class Display
{
private:
    const float SCREEN_HEIGHT = 600.f;
    const float SCREEN_WIDTH = 800.f;
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
    void update(GLuint vao, Shader shader, Camera& camera);
    // Takes a vao and shader for drawing
    void render();
    void setBackgroundColour(GLclampf r, GLclampf g, GLclampf b, GLclampf a);
};
