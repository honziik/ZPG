#include "Transform.h"
class Translate : public Transform {
private:
    glm::vec3 translation;

public:
    Translate(const glm::vec3& translation) : translation(translation) {}

    glm::mat4 getMatrix() const override {
        return glm::translate(glm::mat4(1.0f), translation);
    }
};