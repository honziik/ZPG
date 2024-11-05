#include "Scene.h"
#include <iostream>
#include "Tree.h"
#include "Bushes.h"
#include "CompositTransform.cpp"
#include "Translate.cpp"
#include "Scale.cpp"
#include "Rotate.cpp"
#include "Square.h"

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

void Scene::render() {
 
    float aspectRatio = 1600.0f / 1200.0f;
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

    for (DrawableObject* object : objects) {
        glm::mat4 modelMatrix = object->getModelMatrix();

        camera->notifyObservers();
        object->getShaderProgram()->use();
        object->getShaderProgram()->setUniformMatrix4fv("modelMatrix", glm::value_ptr(modelMatrix));
        object->getShaderProgram()->setUniformMatrix4fv("projectionMatrix", glm::value_ptr(projectionMatrix));
        object->draw();
    }
}