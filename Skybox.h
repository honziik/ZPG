#pragma once
#include "ShaderProgram.h"
#include <vector>
#include <string>
#include <../../libs/stb/stb_image.h>
#include <glm/gtc/type_ptr.hpp>
#include "Observer.h"

class Skybox : public Observer {
public:
    Skybox(Camera* camera);
    ~Skybox();

    void init();
    void loadCubemap(const std::vector<std::string>& faces);
    void draw(bool followCamera);
    void setShader(ShaderProgram* shader);
    void update();

private:
    Camera* camera;
    glm::mat4 viewMatrix;
    GLuint VAO, VBO, cubemapTexture;
    ShaderProgram* shader;
    std::vector<std::string> faces;
};