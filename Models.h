#pragma once
#include <GL/glew.h>
#include "ShaderProgram.h"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp> 
#include <glm/mat4x4.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "DrawableObject.h"

class Models : public DrawableObject {
    public:
        Models(const float* vertices, int vertexCount, bool hasNormals);
        ~Models();

        GLuint getVAO();
        int getVertexCount();
        void draw();
        void setTransform(Transform* t);
        glm::mat4 getModelMatrix();

    private:
        GLuint VBO;
        GLuint VAO;
        int vertexCount;
        Transform* transform;
};