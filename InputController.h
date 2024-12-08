#pragma once
#include "Scene.h"
#include "SceneManager.h"
class InputController {
public:
    InputController(GLFWwindow* window, SceneManager* sceneManager);

    void processInput(float deltaTime);

private:
    GLFWwindow* window;
    SceneManager* sceneManager;

    bool cursorLocked = false;
    float lastSwitchTime = 0.0f;
    float switchDelay = 0.5f;

    void handleMouseInput(Scene* scene, float currentTime);
    void handleMove(Scene* scene, float deltaTime);
    void handleKeyboardInput(Scene* scene, float currentTime);
};
