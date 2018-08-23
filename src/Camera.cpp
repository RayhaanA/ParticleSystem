#include "Camera.h"
#include <gtc\matrix_transform.hpp>
#include <iostream>
Camera::Camera()
{
    position = glm::vec3(0.0f, 0.0f, 40.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    speed = 0.03f;
    pitch = 0.0f;
    yaw = 0.0f;
    fov = 45.0f;
    sensitivity = 0.005f;
    orientation = glm::quat();
}

Camera::~Camera()
{
}

void Camera::updateCameraView()
{
    // Create orientation quaternion delta from pitch and yaw deltas from mouse movement
    glm::quat q = glm::quat(glm::vec3(pitch, yaw, 0.0f));
    
    // Reset deltas
    pitch = yaw = 0.0f;

    // Update orientation quaternion
    orientation = q * orientation;
    orientation = glm::normalize(orientation);

    // Update view matrix with quaternion and position
    view = glm::mat4(orientation) * glm::translate(glm::mat4(1.0f), -position);
}
