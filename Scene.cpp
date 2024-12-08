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
#include "BezierMove.cpp"

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

void Scene::removeObject(int index)
{
    delete objects[index - 1];
    objects.erase(objects.begin() + (index - 1));
}

void Scene::addObject(glm::vec3 position)
{
    std::vector<Transform*> transforms;
    transforms.push_back(new Translate(position));

    addObject(ModelFactory::createModel(tree, 92814, shaders[0], transforms));
 
}

void Scene::addBObject()
{
    if (controlPoints.size() >= 4 && (controlPoints.size() - 1) % 3 == 0) {
        std::vector<Transform*> transforms;
        transforms.push_back(new BezierMove(controlPoints, 0.5f));
        transforms.push_back(new Scale(glm::vec3(3.0f, 3.0f, 3.0f)));

        addObject(ModelFactory::createModelFromObject("objects/zombie.obj", "textures/zombie.png", shaders[1], transforms));
        controlPoints.clear();
    }
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
       
        objects[i]->getShaderProgram()->use();
        objects[i]->getShaderProgram()->setUniformMatrix4fv("modelMatrix", glm::value_ptr(modelMatrix));
        objects[i]->getShaderProgram()->setUniformMatrix4fv("projectionMatrix", glm::value_ptr(projectionMatrix));
        glStencilFunc(GL_ALWAYS, i + 1, 0xFF);
        objects[i]->draw();
    }
}