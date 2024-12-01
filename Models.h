#pragma once
#include <GL/glew.h>
#include <assimp/Importer.hpp>// C++ importerinterface
#include <assimp/scene.h>// aiSceneoutputdata structure
#include <assimp/postprocess.h>// Post processingflags
#include "ShaderProgram.h"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp> 
#include <glm/mat4x4.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "DrawableObject.h"
#include "Texture.h" 
class Models : public DrawableObject {
    public:
        Models(const float* vertices, int vertexCount, bool hasNormals, bool hasUVs);
        Models(const std::string& fileName, const std::string& textureName);
        bool loadFromFile(const std::string& fileName, const std::string& textureName);
        ~Models();
        void draw();
        glm::mat4 getModelMatrix();
        int getVertexCount();
        void setTexture(Texture* tex);
private:
    GLuint IBO;                // Index Buffer Object (optional)
    int indexCount;            // Number of indices (if any)
    bool hasIBO;               // True if an Index Buffer Object is used
    int vertexCount;
    int indicesCount;
    Texture* texture;
};