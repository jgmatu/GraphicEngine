#include "Transform.hpp"


Transform::Transform() :
    _x(0),
    _y(0),
    _z(0)
{
    ;
}

Transform::~Transform() {
    ;
}

void Transform::identity() {
    _model = glm::mat4(1.0);
}

void Transform::translate(glm::vec3 vec3) {
    _model *= glm::translate(_model, vec3);
}

void Transform::scale(glm::vec3 vec3) {
    _model *= glm::scale(_model, vec3);
}

void Transform::rotate(float angle, glm::vec3 direction) {
    _model *= glm::rotate(angle, direction);
}

glm::mat4 Transform::model() {
    return _model;
}

void Transform::move() {
    _model = glm::translate(_model, glm::vec3(_x, _y, _z));
}
