#pragma once
#include <glm.hpp>
#include <gtc\quaternion.hpp>

struct Camera
{
private:
public:
    Camera();
    ~Camera();
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 front;
    glm::mat4 view;
    glm::quat orientation;
    float pitch;
    float yaw;
    float speed;
    float fov;
    float sensitivity;
    void updateCameraView();
};
