#pragma once
#include "Light.h"

class PointLight : public Light {
public:
    PointLight(const glm::vec3& position, const glm::vec3& color, float constant, float linear, float quadratic);

    float getConstant() const;
    float getLinear() const;
    float getQuadratic() const;

private:
    float constant;
    float linear;
    float quadratic;
};