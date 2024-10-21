#include "Square.h"
#include <GL/glew.h>

Square::Square() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    color[0] = 1.0f;
    color[1] = 1.0f;
    color[2] = 1.0f;
    color[3] = 1.0f;
}

Square::~Square() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Square::setVertices(float* vertices, int size) {
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Square::setColor(float r, float g, float b, float a) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
    color[3] = a;
}

void Square::draw(GLuint shaderProgram) {
    glBindVertexArray(VAO);

    GLint colorLocation = glGetUniformLocation(shaderProgram, "color");
    glUniform4f(colorLocation, color[0], color[1], color[2], color[3]);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}