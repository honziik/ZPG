#include "Transform.h"
class DynamicRotate : public Transform {
private:
    glm::vec3 axis;
    float rotationSpeed = glm::radians(1.0f);
public:
    mutable float angle;
    DynamicRotate(float angle, const glm::vec3& axis) : angle(angle), axis(axis) {}

    glm::mat4 getMatrix() const override {
        this->angle += rotationSpeed;
        return glm::rotate(glm::mat4(1.0f), angle, axis);
    }
};