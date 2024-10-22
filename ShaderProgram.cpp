
#include "ShaderProgram.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader, Camera* camera) {
    GLuint vertex = compileShader(GL_VERTEX_SHADER, vertexShader);
    GLuint fragment = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
    this->camera = camera;

    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);

    // Check if linking succeeded
    GLint success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

        // Ensure that the shader program is not used if linking fails
        glDeleteProgram(id);
        id = 0; // Reset program ID to indicate it is not valid
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
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
    glm::mat4 viewMatrix = camera->getViewMatrix();
    setUniformMatrix4fv("viewMatrix", glm::value_ptr(viewMatrix));
}

