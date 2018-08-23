#include "Display.h"
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <iostream>
#include "InputManager.h"

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

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Particle System", nullptr, nullptr);

    if (!window) 
    {
        std::cerr << "Couldn't open GLFW window!" << std::endl;
        glfwTerminate();
    }
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

Display::~Display()
{
    glfwTerminate();
}

GLFWwindow* Display::getWindow()
{
    return window;
}

void Display::update(GLuint vao, Shader shader, Camera& camera)
{
    glClearColor(backgroundColour.r, backgroundColour.g, backgroundColour.b, backgroundColour.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.useShader();

    // update the uniform color
    float timeValue = glfwGetTime();
    float greenValue = sin(timeValue) / 2.0f + 0.5f;

    shader.set4fv("newColour", glm::vec4(1.0, 0.4, greenValue, 1.0));

    glm::mat4 model, view, projection;
    model = glm::rotate(model, timeValue, glm::vec3(0.0f, 0.0f, 1.0f));
    view = camera.view;
    projection = glm::perspective(glm::radians(camera.fov), SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);

    shader.setMatrix4fv("model", model);
    shader.setMatrix4fv("view", view);
    shader.setMatrix4fv("projection", projection);

    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, 6);
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