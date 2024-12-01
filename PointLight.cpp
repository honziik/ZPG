#include "PointLight.h"

PointLight::PointLight(const glm::vec3& position, const glm::vec3& color, float constant, float linear, float quadratic)
    : Light(position, color), constant(constant), linear(linear), quadratic(quadratic) {}

float PointLight::getConstant() const {
    return constant;
}

float PointLight::getLinear() const {
    return linear;
}

float PointLight::getQuadratic() const {
    return quadratic;
}