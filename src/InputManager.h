#pragma once
#include <glfw3.h>
#include "Camera.h"

namespace InputManager
{
    void processKeyPress(GLFWwindow* window, Camera& camera);
    void processMouseMove(GLFWwindow* window, double x, double y, double& oldX, double& oldY, Camera& camera);
}
