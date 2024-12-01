#pragma once
#include "Light.h"
#include "Observer.h"
#include "Camera.cpp"

class Spotlight : public Light, public Observer {
public:
    Spotlight(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color,
        float innerCutoff, float outerCutoff);

    const glm::vec3& getDirection() const;
    float getInnerCutoff() const;
    float getOuterCutoff() const;
    void update();
    void attachToCamera(Camera* cam);

private:
    glm::vec3 direction;
    float innerCutoff;
    float outerCutoff;
    Camera* camera;
};