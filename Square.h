#pragma once
#ifndef SQUARE_H
#define SQUARE_H

#include "Model.h"

class Square : public Model {
public:
    Square();
    ~Square();
    void draw(GLuint shaderProgram) override;
    void setVertices(float* vertices, int size) override;
    void setColor(float r, float g, float b, float a) override;

private:
    GLuint VAO, VBO;
    float color[4];
};

#endif
