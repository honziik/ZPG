#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Scene.h"

class Application {
public:
    Application();
    ~Application();
    void run();

private:
    Scene* scene; 
};