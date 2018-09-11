#include "Camera.h"
#include <gtc\matrix_transform.hpp>
#include <gtx\quaternion.hpp>
#include <iostream>

Camera::Camera()
{
    _position = { 0.0f, 0.0f, 50.0f };
    _up = { 0.0f, 1.0f, 0.0f };
    _direction = { 0.0f, 0.0f, -1.0f };
    _speed = 0.03f;
    _pitch = 0.0f;
    _yaw = 0.0f;
    _fov = 45.0f;
    _sensitivity = 0.0025f;
}

void Camera::updateCameraView()
{   
    glm::quat qPitch = glm::angleAxis(_pitch, glm::vec3(1, 0, 0));
    glm::quat qYaw = glm::angleAxis(_yaw, glm::vec3(0, 1, 0));

    // Combine rotations
    glm::quat orientation = qPitch * qYaw;
    orientation = glm::normalize(orientation);

    // Create matrix from quaternions
    glm::mat4 rotate = glm::mat4_cast(orientation);
    glm::mat4 translate = glm::mat4(1.0f);
    translate = glm::translate(translate, -_position);

    _view = rotate * translate;

    // Get new direction vector from view matrix
    _direction = getViewDirection();
}

void Camera::setViewDirection(glm::vec3 d)
{
    _view[0][2] = d.x;
    _view[1][2] = d.y;
    _view[2][2] = d.z;
}

glm::vec3 Camera::getViewDirection() const
{
    return -glm::normalize(glm::vec3(_view[0][2], _view[1][2], _view[2][2]));
}

float& Camera::pitch()
{
    return _pitch;
}

float& Camera::yaw()
{
    return _yaw;
}

float& Camera::speed()
{
    return _speed;
}

float& Camera::fov()
{
    return _fov;
}

float& Camera::sensitivity()
{
    return _sensitivity;
}

glm::vec3& Camera::position()
{
    return _position;
}

glm::vec3& Camera::up()
{
    return _up;
}

glm::vec3& Camera::direction()
{
    return _direction;
}

glm::mat4& Camera::view()
{
    return _view;
}