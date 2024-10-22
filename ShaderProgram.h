#pragma once
#include <string>
#include <GL/glew.h>
#include "Camera.cpp"

class ShaderProgram : public Observer {
public:
    ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader, Camera* camera);
    ~ShaderProgram();


    void use();
    GLuint getUniformLocation(const std::string& name);
    void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void setUniformMatrix4fv(const std::string& name, const GLfloat* value);
    void update();

private:
    Camera* camera;
    GLuint id;
    GLuint compileShader(GLenum type, const std::string& source);
};