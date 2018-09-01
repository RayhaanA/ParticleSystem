#pragma once
#include <glm.hpp>

class Camera
{
private:
    glm::vec3 _position;
    glm::vec3 _up;
    glm::vec3 _direction;
    glm::mat4 _view;
    float _pitch;
    float _yaw;
    float _speed;
    float _fov;
    float _sensitivity;

public:
    float DEFAULT_CAM_SPEED = 0.03f;
    float SHIFT_CAM_SPEED = 0.2f;
    Camera();
    ~Camera() = default;
    void updateCameraView();
    void setViewDirection(glm::vec3 d);
    glm::vec3 getViewDirection() const;

    glm::vec3& position();
    glm::vec3& up();
    glm::vec3& direction();
    glm::mat4& view();
    float& pitch();
    float& yaw();
    float& speed();
    float& fov();
    float& sensitivity();
};
