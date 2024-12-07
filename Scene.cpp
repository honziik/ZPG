#include "Scene.h"
#include <iostream>
#include "Tree.h"
#include "Bushes.h"
#include "CompositTransform.cpp"
#include "Translate.cpp"
#include "Scale.cpp"
#include "Rotate.cpp"
#include "Square.h"
#include "Firefly.h"

Scene::Scene(Camera* camera) {
    this->camera = camera;
    this->skybox = nullptr;
    this->isNotSkybox = false; 
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

void Scene::addSkybox(Skybox* skybox)
{
    this->skybox = skybox;
}

void Scene::changeSkybox()
{
    this->isNotSkybox = !this->isNotSkybox;
}

void Scene::render() {
    glm::mat4 projectionMatrix = camera->getProjectionMatrix();
    camera->notifyObservers();

    if (skybox) {
        skybox->draw(isNotSkybox);
    }

    for (int i = 0; i < objects.size(); i++) {
        glm::mat4 modelMatrix = objects[i]->getModelMatrix();

        Firefly* firefly = dynamic_cast<Firefly*>(objects[i]);
        if (firefly) {
            firefly->update();
        }

        //todo create model factory, function for skybox 
       
        objects[i]->getShaderProgram()->use();
        objects[i]->getShaderProgram()->setUniformMatrix4fv("modelMatrix", glm::value_ptr(modelMatrix));
        objects[i]->getShaderProgram()->setUniformMatrix4fv("projectionMatrix", glm::value_ptr(projectionMatrix));
        glStencilFunc(GL_ALWAYS, i + 1, 0xFF);
        objects[i]->draw();
    }
}