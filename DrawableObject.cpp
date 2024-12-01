#include "DrawableObject.h"

void DrawableObject::setShaderProgram(ShaderProgram* shader) {
    this->shaderProgram = shader;
}

ShaderProgram* DrawableObject::getShaderProgram()
{
    return shaderProgram;
}

GLuint DrawableObject::getVAO()
{
    return this->VAO;
}
