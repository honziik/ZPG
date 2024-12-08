#pragma once
#include <GLFW/glfw3.h>
#include "Transform.h"
class LinearMove : public Transform {
public:
    LinearMove(const glm::vec3& translation, const glm::vec3& direction, float speed) : translation(translation), direction(direction), speed(speed) {}

    glm::mat4 getMatrix() const override {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        translation += direction * speed * deltaTime;

        totalElapsedTime += deltaTime;
        if (totalElapsedTime >= 2.0f) {
            direction = -direction;
            totalElapsedTime = 0.0f; 
        }
        return glm::translate(glm::mat4(1.0f), translation);
    }
private:
    mutable glm::vec3 translation;
    mutable glm::vec3 direction;
    float speed;
    mutable float lastTime = 0.0f;
    mutable float totalElapsedTime = 0.0f;
};