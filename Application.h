#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "SceneManager.h"
#include <iostream>
#include "Camera.cpp"
#include "SceneFactory.h"

class Application {

private:
    void processInput(GLFWwindow* window, float deltaTime);

public:
    Application();
    ~Application();
    void run();

};
