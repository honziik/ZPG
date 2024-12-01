#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const glm::vec3& direction, const glm::vec3& color)
    : Light(glm::vec3(0.0f), color), direction(direction) {}

const glm::vec3& DirectionalLight::getDirection() const {
    return direction;
}