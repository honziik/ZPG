#include "Transform.h"

class Scale : public Transform {
private:
    glm::vec3 scale;

public:
    Scale(const glm::vec3& scale) : scale(scale) {}

    glm::mat4 getMatrix() const override {
        return glm::scale(glm::mat4(1.0f), scale);
    }
};