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
#include "Camera.h"

class Scene {
public:
    Scene();
    void render();
    void addObject(DrawableObject* object);
    void setCamera(Camera* camera);

private:
    std::vector<DrawableObject*> objects;
    Camera* camera;
};
