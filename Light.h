#pragma once
#include "Observer.h"
#include <glm/glm.hpp>
#include <vector>

class Light{
public:
    Light(const glm::vec3& position, const glm::vec3& color);
    virtual ~Light() {}
    const glm::vec3& getPosition() const;
    const glm::vec3& getColor() const;

    void addObserver(Observer* observer);
    void notifyObservers();

private:
    std::vector<Observer*> observers;
protected:
    glm::vec3 position;
    glm::vec3 color;
};