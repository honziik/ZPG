#include "Light.h"

Light::Light(const glm::vec3& position, const glm::vec3& color)
    : position(position), color(color) {}

void Light::addObserver(Observer* observer)
{
    observers.push_back(observer);
}

void Light::notifyObservers() {
    for (Observer* observer : observers) {
        observer->update();
    }
}
