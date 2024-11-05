#pragma once
#include <string>
#include <GL/glew.h>
#include "Camera.cpp"
#include "Light.h"
#include "ShaderLoader.h"

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
    void setLight(Light* light);

private:
    Camera* camera;
    Light* light;
    GLuint id;
    GLuint compileShader(GLenum type, const std::string& source);
};