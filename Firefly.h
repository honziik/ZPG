#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "PointLight.h"
#include "Models.h"
#include "Sphere.h"
#include "Observer.h"
#include <random>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/transform.hpp>
#include <chrono>

class Firefly : public Models, public PointLight, public Observer {
public:
    Firefly(glm::vec3 position, glm::vec3 color)
        : PointLight(position, color, 1.0f, 0.18f, 0.064f), Models(sphere, 2880, true, false),
        generator(std::random_device{}()), randomDirection(-1.0f, 1.0f) {
        this->position = position;
        addTranform();
        velocity = glm::vec3(0.0f);
        counter = 0;
        lastUpdate = std::chrono::steady_clock::now();
    }

    void update();

private:
    void addTranform();
    void changeTransform();

    glm::vec3 velocity;
    int counter;
    std::default_random_engine generator;
    std::uniform_real_distribution<float> randomDirection;
    std::chrono::steady_clock::time_point lastUpdate;
};
