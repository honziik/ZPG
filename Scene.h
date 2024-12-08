#pragma once

#include<vector>
#include "DrawableObject.h"
#include "Tree.h"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp> 
#include <glm/mat4x4.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Models.h"
#include "Camera.cpp"
#include "Skybox.h"
#include "ModelFactory.h"

class Scene {
public:
    std::vector<glm::vec3> controlPoints;
    Scene(Camera* camera);
    void render();
    void addObject(DrawableObject* object);
    void addShader(ShaderProgram* shader);
    void init();
    Camera* getCamera();
    void addSkybox(Skybox* skybox);
    void changeSkybox();
    void removeObject(int index);
    void addObject(glm::vec3 position);
    void addBObject();

private:
    std::vector<DrawableObject*> objects;
    std::vector<ShaderProgram*> shaders;
    Camera* camera;
    Skybox* skybox;
    bool isNotSkybox;
};
