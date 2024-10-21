#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <GL/glew.h> 
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include "ShaderProgram.h"
class Camera {
public:
    // Atributy kamery
    glm::vec3 Position;
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    int width, height;
    float speed = 0.1f;
    float sensitivity = 100.0f;
    bool firstClick = true;

    // Konstruktor
    Camera(int width, int height, glm::vec3 position);

    // Aktualizace kamerové matice a její poslání do shaderu
    void updateMatrix(float FOVdeg, float nearPlane, float farPlane);

    // Zpracování uživatelského vstupu (klávesnice, myš)
    void processInputs(GLFWwindow* window);
    void exportMatrix(ShaderProgram& shader, const char* uniform);
private:
    glm::mat4 cameraMatrix;
};