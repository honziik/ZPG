#pragma once
#include "ShaderProgram.h"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp> 
#include <glm/mat4x4.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Transform.h"

class DrawableObject {
public:
    virtual void draw() = 0;
    void setShaderProgram(ShaderProgram* shader);
    ShaderProgram* getShaderProgram();
    virtual glm::mat4 getModelMatrix() = 0;
    virtual void setTransform(Transform* transform) = 0;

private:
    ShaderProgram* shaderProgram;
};
