#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#define GLM_ENABLE_EXPERIMENTAL
#include <string>
#include <iostream>

class Texture {
public:
    Texture();
    ~Texture();

    void loadFromFile(const std::string& filePath);
    void bind() const;
    void unbind() const;

private:
    GLuint textureID;
};

