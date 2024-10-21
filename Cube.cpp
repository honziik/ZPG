#include "Cube.h"
#include <GL/glew.h>

Cube::Cube() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    color[0] = 1.0f;
    color[1] = 1.0f;
    color[2] = 1.0f;
    color[3] = 1.0f;
}

Cube::~Cube() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Cube::setVertices(float* vertices, int size) {
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Cube::setColor(float r, float g, float b, float a) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
    color[3] = a;
}

void Cube::draw(GLuint shaderProgram) {
    glBindVertexArray(VAO);

    GLint colorLocation = glGetUniformLocation(shaderProgram, "color");
    glUniform4f(colorLocation, color[0], color[1], color[2], color[3]);

    //6 surface * 2 triangles * 3 points = 36
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
}
