#include "DrawableObject.h"

void DrawableObject::setShaderProgram(ShaderProgram* shader) {
    this->shaderProgram = shader;
}

ShaderProgram* DrawableObject::getShaderProgram()
{
    return shaderProgram;
}