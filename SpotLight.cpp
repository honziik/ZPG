#include "SpotLight.h"
#include <iostream>

Spotlight::Spotlight(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color,
    float innerCutoff, float outerCutoff)
    : Light(position, color), direction(direction), innerCutoff(innerCutoff), outerCutoff(outerCutoff) {
    camera = nullptr;
}

const glm::vec3& Spotlight::getDirection() const {
    return direction;
}

float Spotlight::getInnerCutoff() const {
    return innerCutoff;
}

float Spotlight::getOuterCutoff() const {
    return outerCutoff;
}

void Spotlight::update()
{
    if (camera) {
        this->position = camera->position;
        this->direction = camera->front;
    }
    notifyObservers();
}

void Spotlight::attachToCamera(Camera* cam)
{
    this->camera = cam;
}

