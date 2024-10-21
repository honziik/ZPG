#pragma once
#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <GL/glew.h>

class Shader {
public:
    Shader(const char* vertexSource, const char* fragmentSource);
    ~Shader();

    void use();
    GLuint getProgram() const;

private:
    GLuint program;
    void checkCompileErrors(GLuint shader, const std::string& type);
};

#endif
