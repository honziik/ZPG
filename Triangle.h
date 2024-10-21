#pragma once

#include "DrawableObject.h"
#include <GL/glew.h>

class Triangle : public DrawableObject {
public:
    Triangle();
    void draw();

private:
    GLuint VAO, VBO;
};
