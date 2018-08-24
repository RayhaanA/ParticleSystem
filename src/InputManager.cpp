#include "InputManager.h"
#include <iostream>

void InputManager::processKeyPress(GLFWwindow* window, Camera& camera)
{   
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        camera.speed() = 0.2f;
    }
    else
    {
        camera.speed() = 0.03f;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.position() += camera.speed() * camera.direction();
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.position() -= camera.speed() * camera.direction();
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.position() -= glm::cross(camera.direction(), camera.up()) * camera.speed();
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.position() += glm::cross(camera.direction(), camera.up()) * camera.speed();
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        camera.pitch() = 0.0f;
        camera.yaw() = 0.0f;
        camera.position() = glm::vec3(0.0f, 0.0f, 30.0f);
        camera.direction() = glm::vec3(0.0f, 0.0f, -1.0f);
        camera.view()[0][2] = 0.0f;
        camera.view()[1][2] = 0.0f;
        camera.view()[2][2] = -1.0f;
    }
}

void InputManager::processMouseMove(GLFWwindow* window, double x, double y, double& oldX, double& oldY, Camera& camera)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glm::vec2 delta = glm::vec2(x, y) - glm::vec2(oldX, oldY);

        delta *= camera.sensitivity();

        camera.yaw() += delta.x;
        camera.pitch() += delta.y;

        if (camera.pitch() > 1.0f)
        {
            camera.pitch() = 1.0f;
        }
        else if (camera.pitch() < -1.0f)
        {
            camera.pitch() = -1.0f;
        }
    }

    camera.updateCameraView();
}