#pragma once
#include "Observer.h"
#include <glm/glm.hpp>
#include <vector>

class Light
{
public:
    Light(const glm::vec3& position, const glm::vec3& color);


    void addObserver(Observer* observer);
    void notifyObservers();

    glm::vec3 position;
    glm::vec3 color;
 private:
    std::vector<Observer*> observers;
};