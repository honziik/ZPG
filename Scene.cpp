#include "Scene.h"
#include <iostream>
#include "Tree.h"
#include "Bushes.h"
#include "CompositTransform.cpp"
#include "Translate.cpp"
#include "Scale.cpp"
#include "Rotate.cpp"
#include "Square.h"

float rotationSpeed = glm::radians(1.0f);

Scene::Scene(Camera* camera) {
    this->camera = camera;
}

void Scene::addObject(DrawableObject* object) {
    objects.push_back(object);
}

void Scene::addShader(ShaderProgram* shader)
{
    this->shaders.push_back(shader);
}

void Scene::init()
{
    for (ShaderProgram* shaderProgram : shaders) {
        camera->addObserver(shaderProgram);
    }
}

Camera* Scene::getCamera()
{
    return this->camera;
}
void Scene::render(float aspectRatio) {
 
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

    for (DrawableObject* object : objects) {
        glm::mat4 modelMatrix = object->getModelMatrix();

        
        Models* modelObject = dynamic_cast<Models*>(object);
        if (modelObject && modelObject->getVertexCount() == 92814 || modelObject->getVertexCount() == 2880) {
            CompositeTransform* compositeTransform = dynamic_cast<CompositeTransform*>(modelObject->transform);

            if (compositeTransform) {
                Rotate* rotateTransform = compositeTransform->getFirstTransform<Rotate>();

                if (rotateTransform) {
                    rotateTransform->angle += rotationSpeed;
                    if (rotateTransform->angle > glm::two_pi<float>()) {
                        rotateTransform->angle -= glm::two_pi<float>();
                    }
                }
                else {
                    rotateTransform = new Rotate(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
                    compositeTransform->addTransform(rotateTransform);
                }
            }
        }

        camera->notifyObservers();
        object->getShaderProgram()->use();
        object->getShaderProgram()->setUniformMatrix4fv("modelMatrix", glm::value_ptr(modelMatrix));
        object->getShaderProgram()->setUniformMatrix4fv("projectionMatrix", glm::value_ptr(projectionMatrix));

        object->draw();
    }
}