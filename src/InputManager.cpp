#include "InputManager.h"
#include <iostream>

void InputManager::processKeyPress(GLFWwindow* window, Camera& camera)
{   
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.position += camera.speed * camera.front;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.position -= camera.speed * camera.front;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.position -= glm::normalize(glm::cross(camera.front, camera.up)) * camera.speed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.position += glm::normalize(glm::cross(camera.front, camera.up)) * camera.speed;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        camera.front = glm::vec3(0.0f, 0.0f, -1.0f);
    }
}

void InputManager::processMouseMove(GLFWwindow* window, double x, double y, double& oldX, double& oldY, Camera& camera)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glm::vec2 delta = glm::vec2(x, y) - glm::vec2(oldX, oldY);

        delta *= camera.sensitivity;

        camera.yaw += delta.x;
        camera.pitch += delta.y;

        if (camera.pitch > 89.0f)
        {
            camera.pitch = 89.0f;
        }
        else if (camera.pitch < -89.0f)
        {
            camera.pitch = -89.0f;
        }
    }
    camera.updateCameraView();
}