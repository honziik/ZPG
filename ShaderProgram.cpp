
#include "ShaderProgram.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader, Camera* camera) {
    ShaderLoader shaderLoader(vertexShader.c_str(), fragmentShader.c_str(), &id);

    this->camera = camera;
    this->light = nullptr;

    if (id == 0) {
        std::cerr << "ERROR::SHADER::PROGRAM::CREATION_FAILED\n";
    }
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(id);
}

void ShaderProgram::use() {
    if (id != 0) { 
        glUseProgram(id);
    }
    else {
        std::cerr << "ERROR::SHADER::PROGRAM::USE_FAILED - Shader program not valid!" << std::endl;
    }
}

GLuint ShaderProgram::compileShader(GLenum type, const std::string& source) {
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}

GLuint ShaderProgram::getUniformLocation(const std::string& name) {
    return glGetUniformLocation(id, name.c_str());
}

void ShaderProgram::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}
void ShaderProgram::setUniformMatrix4fv(const std::string& name, const GLfloat* value) {
    GLuint location = getUniformLocation(name);  // Najde umístìní uniformní promìnné
    if (location != -1) {
        glUniformMatrix4fv(location, 1, GL_FALSE, value);  // Nastaví matici
    }
    else {
        std::cerr << "Warning: uniform '" << name << "' not found." << std::endl;
    }
}

void ShaderProgram::update()
{
    use();
    glm::mat4 viewMatrix = camera->getViewMatrix();
    setUniformMatrix4fv("viewMatrix", glm::value_ptr(viewMatrix));
    if (light != nullptr) {
        setUniform3f("lightPosition", light->position.x, light->position.y, light->position.z);
        setUniform3f("lightColor", light->color.x, light->color.y, light->color.z);
        setUniform3f("viewPos", camera->position.x, camera->position.y, camera->position.z);
    }
}

void ShaderProgram::setUniform3f(const std::string& name, float v0, float v1, float v2)
{
    GLuint location = getUniformLocation(name);
    if (location != -1) {
        glUniform3f(location, v0, v1, v2);
    }
}

void ShaderProgram::setLight(Light* light)
{
    this->light = light;
}

