#include "Models.h"

Models::Models(const float* vertices, int vertexCount, bool hasNormals)
    : vertexCount(vertexCount)
{
    // Generate and bind VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Initialize buffer data
    glBufferData(GL_ARRAY_BUFFER, (hasNormals ? vertexCount * 6 * sizeof(float) : vertexCount * 3 * sizeof(float)), vertices, GL_STATIC_DRAW);


    // Set position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (hasNormals ? 6 * sizeof(float) : 3 * sizeof(float)), (GLvoid*)0);

    // Set normal attribute if available
    if (hasNormals) {
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    }

    // Unbind VAO and VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}



GLuint Models::getVAO() {
    return this->VAO;
}

int Models::getVertexCount() {
    return this->vertexCount;
}

void Models::draw()
{
    getShaderProgram()->use();
    glBindVertexArray(this->getVAO());
    glDrawArrays(GL_TRIANGLES, 0, this->getVertexCount());
    // Unbind VAO
    glBindVertexArray(0);

}

void Models::setTransform(Transform* t)
{
    this->transform = t;
}

glm::mat4 Models::getModelMatrix()
{
    return transform ? transform->getMatrix() : glm::mat4(1.0f);
}

Models::~Models() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}