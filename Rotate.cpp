#include "Transform.h"
class Rotate : public Transform {
private:
    glm::vec3 axis;

public:
    float angle;
    Rotate(float angle, const glm::vec3& axis) : angle(angle), axis(axis) {}

    glm::mat4 getMatrix() const override {
        return glm::rotate(glm::mat4(1.0f), angle, axis);
    }
};