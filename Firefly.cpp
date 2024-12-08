#include "Firefly.h"
#include "CompositTransform.cpp"
#include "Scale.cpp"
#include "Translate.cpp"


void Firefly::update() {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate).count();

    if (elapsed > 10) {
        changeTransform();
        lastUpdate = now;
    }
}

void Firefly::addTranform() {

    CompositeTransform* cTransform = new CompositeTransform();
    cTransform->addTransform(new Translate(position));
    cTransform->addTransform(new Scale(glm::vec3(0.2f, 0.2f, 0.2f)));
    this->transform = cTransform;
}


void Firefly::changeTransform() {
    if (counter % 10 == 0) { 
        velocity += glm::vec3(
            randomDirection(generator),
            randomDirection(generator),
            randomDirection(generator)
        );

        float length = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z);
        if (length > 0) {
            velocity /= length;
        }
    }
    counter++;

   
    float stepSize = 0.1f;
    position += velocity * stepSize;
    if (position.y < 0.0f) {
        position.y = 0.1f;
    }
    if (position.y > 15.0f) {
        position.y = 14.9f;
    }

    CompositeTransform* compositeTransform = dynamic_cast<CompositeTransform*>(this->transform);
    if (compositeTransform) {
        Translate* translateTransform = compositeTransform->getFirstTransform<Translate>();
        if (translateTransform) {
                translateTransform->translation = position;
        }
    }
}
