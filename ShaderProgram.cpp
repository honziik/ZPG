#include "ShaderProgram.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "PointLight.h"

ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader, Camera* camera) {
    ShaderLoader shaderLoader(vertexShader.c_str(), fragmentShader.c_str(), &id);

    this->camera = camera;

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
    GLuint location = getUniformLocation(name);
    if (location != -1) {
        glUniformMatrix4fv(location, 1, GL_FALSE, value);
    }
    else {
        std::cerr << "Warning: uniform '" << name << "' not found." << std::endl;
    }
}

void ShaderProgram::update() {
    use();

    glm::mat4 viewMatrix = camera->getViewMatrix();
    GLuint location = getUniformLocation("grassTexture");
    if (location != -1) {
        setUniform1i("grassTexture", 0);
    }
    location = getUniformLocation("viewMatrix");
    if (location != -1) {
        setUniformMatrix4fv("viewMatrix", glm::value_ptr(viewMatrix));
    }
    location = getUniformLocation("viewPos");
    if (location != -1) {
        setUniform3f("viewPos", camera->position.x, camera->position.y, camera->position.z);
    }
    if (!lights.empty()) {
        setUniform1i("numLights", lights.size());

        for (size_t i = 0; i < lights.size(); ++i) {
            Light* light = lights[i];

            std::string baseName = "lights[" + std::to_string(i) + "]";

            setUniform3fv(baseName + ".position", light->getPosition());
            setUniform3f(baseName + ".color", light->getColor().x, light->getColor().y, light->getColor().z);

            if (auto dirLight = dynamic_cast<DirectionalLight*>(light)) {
                setUniform3f(baseName + ".direction", dirLight->getDirection().x, dirLight->getDirection().y, dirLight->getDirection().z);
                setUniform1i(baseName + ".type", 1);
            }
            else if (auto spotLight = dynamic_cast<Spotlight*>(light)) {
                setUniform3fv(baseName + ".direction", spotLight->getDirection());
                setUniform1f(baseName + ".innerCutoff", spotLight->getInnerCutoff());
                setUniform1f(baseName + ".outerCutoff", spotLight->getOuterCutoff());
                setUniform1i(baseName + ".type", 2);
            }
            else if (auto pointLight = dynamic_cast<PointLight*>(light)) {
                setUniform1f(baseName + ".constant", pointLight->getConstant());
                setUniform1f(baseName + ".linear", pointLight->getLinear());
                setUniform1f(baseName + ".quadratic", pointLight->getQuadratic());
                setUniform1i(baseName + ".type", 0);
            }
        }
    }
}


void ShaderProgram::setUniform1i(const std::string& name, int value) {
    GLuint location = getUniformLocation(name);
    if (location != -1) {
        glUniform1i(location, value);
    }
    else {
        std::cerr << "Warning: uniform '" << name << "' not found." << std::endl;
    }
}

void ShaderProgram::setUniform1f(const std::string& name, float value) {
    GLuint location = getUniformLocation(name);
    if (location != -1) {
        glUniform1f(location, value);
    }
    else {
        std::cerr << "Warning: uniform '" << name << "' not found." << std::endl;
    }
}

void ShaderProgram::setUniform3fv(const std::string& name, glm::vec3 value)
{
    GLuint location = getUniformLocation(name);
    if (location != -1) {
        glUniform3fv(location, 1, glm::value_ptr(value));
    }
    else {
        std::cerr << "Warning: uniform '" << name << "' not found." << std::endl;
    }
}

void ShaderProgram::setUniform3f(const std::string& name, float v0, float v1, float v2)
{
    GLuint location = getUniformLocation(name);
    if (location != -1) {
        glUniform3f(location, v0, v1, v2);
    }
    else {
        std::cerr << "Warning: uniform '" << name << "' not found." << std::endl;
    }
}

void ShaderProgram::addLight(Light* light) {
    lights.push_back(light);
}


