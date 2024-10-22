#pragma once

#include<vector>
#include "DrawableObject.h"
#include "Triangle.h"
#include "Tree.h"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp> 
#include <glm/mat4x4.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Models.h"
#include "Camera.cpp"

class Scene {
public:
    Scene(Camera* camera);
    void render();
    void addObject(DrawableObject* object);
    void init();

private:
    std::vector<DrawableObject*> objects;
    std::vector<ShaderProgram*> shaders;
    Camera* camera;
};
