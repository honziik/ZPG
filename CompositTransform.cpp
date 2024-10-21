#include <vector>
#include "Transform.h"
class CompositeTransform : public Transform {
private:
    std::vector<Transform*> transforms;

public:
    CompositeTransform() {
    }

    void addTransform(Transform* transform) {
        transforms.push_back(transform);
    }

    glm::mat4 getMatrix() const override {
        glm::mat4 result = glm::mat4(1.0f);
        for (int i = 0; i < transforms.size(); i++) {
            result = result * transforms[i]->getMatrix();
        }
        return result;
    }

    ~CompositeTransform() {
        for (auto transform : transforms) {
            delete transform;
        }
    }
};