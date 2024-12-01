#include "Application.h"

SceneManager* sceneManager;
bool firstMouse = true;
float lastX = 400, lastY = 300;

// Nastavení èasového delaye pro pøepínání scén
float lastSwitchTime = 0.0f; // Èas posledního pøepnutí
float switchDelay = 0.5f;    // Delay 0.5 sekundy

float aspectRatio = 1600.0f / 1200.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    Scene* currentScene = sceneManager->getCurrentScene();
    Camera* camera = currentScene->getCamera();
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera->processMouseMovement(xoffset, yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    aspectRatio = static_cast<float>(width) / height;
}

void Application::processInput(GLFWwindow* window, float deltaTime) {
    float currentTime = glfwGetTime();
    Scene* currentScene = sceneManager->getCurrentScene();
    Camera* camera = currentScene->getCamera();

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
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        if (currentTime - lastSwitchTime >= switchDelay) {
            currentScene->changeSkybox();
            lastSwitchTime = currentTime;
        }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        if (currentTime - lastSwitchTime >= switchDelay) {
            sceneManager->switchScene();
            lastSwitchTime = currentTime;
        }
    }
}

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
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(1600, 1200, "OpenGL Application", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEPTH_TEST);
    glDebugMessageCallback(openglDebugCallback, nullptr);
    glViewport(0, 0, 1600, 1200);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    sceneManager = new SceneManager();

    //sceneManager->addScene(SceneFactory::createFifthScene());
    sceneManager->addScene(SceneFactory::createSecondScene());

    sceneManager->addScene(SceneFactory::createFifthScene());
    sceneManager->addScene(SceneFactory::createFirstScene());
    sceneManager->addScene(SceneFactory::createThirdScene());
    sceneManager->addScene(SceneFactory::createFourthScene());
    
    glfwSetCursorPosCallback(window, mouse_callback);
}

void Application::run() {
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(glfwGetCurrentContext())) {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        processInput(glfwGetCurrentContext(), deltaTime);

        Scene* currentScene = sceneManager->getCurrentScene();
        currentScene->render(aspectRatio);

        glfwSwapBuffers(glfwGetCurrentContext());
        glfwPollEvents();
    }
}

Application::~Application() {
    delete sceneManager;
    glfwTerminate();
}
