#include "Camera.hpp"

Camera::Camera() {
    _projection = glm::perspective(glm::radians(60.0f), aspectRatio, 0.001f, 1000.0f);

    _view = glm::mat4(1.0);
    _view = glm::translate(_view, glm::vec3(0.0, 0.0, -5.0));
}

Camera::~Camera() {
    ;
}
