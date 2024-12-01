#pragma once
#include "Light.h"

class DirectionalLight : public Light {
public:
    DirectionalLight(const glm::vec3& direction, const glm::vec3& color);

    const glm::vec3& getDirection() const;

private:
    glm::vec3 direction;
};