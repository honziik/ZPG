#pragma once
#include <string>
#include <GL/glew.h>
#include "Camera.cpp"
#include "Light.h"
#include "ShaderLoader.h"
#include<vector>


class ShaderProgram : public Observer {
public:
    ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader, Camera* camera);
    ~ShaderProgram();


    void use();
    GLuint getUniformLocation(const std::string& name);
    void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void setUniformMatrix4fv(const std::string& name, const GLfloat* value);
    void update();
    void setUniform3f(const std::string& name, float v0, float v1, float v2);
    void addLight(Light* light);
    void setUniform1i(const std::string& name, int value);
    void setUniform1f(const std::string& name, float value);
    void setUniform3fv(const std::string& name, glm::vec3 value);
private:
    Camera* camera;
    std::vector<Light*> lights;
    GLuint id;
    GLuint compileShader(GLenum type, const std::string& source);
};