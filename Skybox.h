#pragma once
#include "ShaderProgram.h"
#include <vector>
#include <string>
#include <../../libs/stb/stb_image.h>
#include <glm/gtc/type_ptr.hpp>

class Skybox {
public:
    Skybox();
    ~Skybox();

    void init();
    void loadCubemap(const std::vector<std::string>& faces);
    void draw(const glm::mat4& view, const glm::mat4& projection, bool followCamera);
    void setShader(ShaderProgram* shader);

private:
    GLuint VAO, VBO, cubemapTexture;
    ShaderProgram* shader;
    std::vector<std::string> faces;
};