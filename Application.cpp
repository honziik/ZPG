#include "Application.h"
#include <iostream>
#include "Camera.h"


void APIENTRY openglDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    std::cerr << "OpenGL Debug Message: " << message << std::endl;
}
Application::Application() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Application", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEPTH_TEST);
    glDebugMessageCallback(openglDebugCallback, nullptr);
    glViewport(0, 0, 800, 600);
    scene = new Scene();
}

void Application::run() {
    //Camera* camera = new Camera(800, 600, glm::vec3(0.0f, 0.0f, 10.0f));
    //scene->setCamera(camera);
    while (!glfwWindowShouldClose(glfwGetCurrentContext())) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //camera->processInputs(glfwGetCurrentContext());
        scene->render();

        glfwSwapBuffers(glfwGetCurrentContext());
        glfwPollEvents();
    }
}

Application::~Application() {
    delete scene;
    glfwTerminate();
}
