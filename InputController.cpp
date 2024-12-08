#include "InputController.h"
#include <iostream>

InputController::InputController(GLFWwindow* window, SceneManager* sceneManager)
    : window(window), sceneManager(sceneManager) {}

void InputController::processInput(float deltaTime) {
    float currentTime = glfwGetTime();
    Scene* currentScene = sceneManager->getCurrentScene();
    handleMove(currentScene, deltaTime);
    if (currentTime - lastSwitchTime < switchDelay) {
        return;
    }

    handleKeyboardInput(currentScene, currentTime);
    handleMouseInput(currentScene, currentTime);

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        sceneManager->switchScene();
        lastSwitchTime = currentTime;
    }

   
}

void InputController::handleKeyboardInput(Scene* scene, float currentTime) {
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        cursorLocked = !cursorLocked;
        glfwSetInputMode(window, GLFW_CURSOR, cursorLocked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
        lastSwitchTime = currentTime;
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        scene->changeSkybox();
        lastSwitchTime = currentTime;
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        scene->addBObject();
        lastSwitchTime = currentTime;
    }
}

void InputController::handleMouseInput(Scene* scene, float currentTime) {
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    int newy = 1200 - y;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        lastSwitchTime = currentTime;
        GLbyte color[4];
        GLfloat depth;
        GLuint index;

        glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
        glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
        glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

        glm::vec3 screenX = glm::vec3(x, newy, depth);
        glm::mat4 view = scene->getCamera()->getViewMatrix();
        glm::mat4 projection = scene->getCamera()->getProjectionMatrix();
        glm::vec4 viewPort = glm::vec4(0, 0, 1600, 1200);
        glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

        scene->removeObject(index);
        std::cout << "unProject [" << pos.x << "," << pos.y << "," << pos.z << "]\n";
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        lastSwitchTime = currentTime;
        GLbyte color[4];
        GLfloat depth;
        GLuint index;

        glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
        glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
        glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

        glm::vec3 screenX = glm::vec3(x, newy, depth);
        glm::mat4 view = scene->getCamera()->getViewMatrix();
        glm::mat4 projection = scene->getCamera()->getProjectionMatrix();
        glm::vec4 viewPort = glm::vec4(0, 0, 1600, 1200);
        glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

        scene->addObject(pos);
        std::cout << "unProject [" << pos.x << "," << pos.y << "," << pos.z << "]\n";
    }

    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
        lastSwitchTime = currentTime;
        GLbyte color[4];
        GLfloat depth;
        GLuint index;

        glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
        glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
        glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

        glm::vec3 screenX = glm::vec3(x, newy, depth);
        glm::mat4 view = scene->getCamera()->getViewMatrix();
        glm::mat4 projection = scene->getCamera()->getProjectionMatrix();
        glm::vec4 viewPort = glm::vec4(0, 0, 1600, 1200);
        glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

        scene->controlPoints.push_back(pos);
        std::cout << "unProject [" << pos.x << "," << pos.y << "," << pos.z << "]\n";
    }
}

void InputController::handleMove(Scene* scene, float deltaTime)
{
    Camera* camera = scene->getCamera();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->processKeyboard('W', deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->processKeyboard('S', deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->processKeyboard('A', deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->processKeyboard('D', deltaTime);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
