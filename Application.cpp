#include "Application.h"
#include "InputController.h"

SceneManager* sceneManager;
bool firstMouse = true;
float lastX = 400, lastY = 300;

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
	sceneManager->getCurrentScene()->getCamera()->aspectRatio = aspectRatio;
}

void APIENTRY openglDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	std::cerr << "OpenGL Debug Message: " << message << std::endl;
}

Application::Application() {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(EXIT_FAILURE);
	}

	GLFWwindow* window = glfwCreateWindow(1600, 1200, "OpenGL Application", nullptr, nullptr);
	if (!window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glDebugMessageCallback(openglDebugCallback, nullptr);
	glViewport(0, 0, 1600, 1200);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	sceneManager = new SceneManager();

	sceneManager->addScene(SceneFactory::createSecondScene());
	sceneManager->addScene(SceneFactory::createFifthScene());
	sceneManager->addScene(SceneFactory::createFirstScene());
	sceneManager->addScene(SceneFactory::createThirdScene());
	sceneManager->addScene(SceneFactory::createFourthScene());

	glfwSetCursorPosCallback(window, mouse_callback);
}

void Application::run() {
	float lastFrame = 0.0f;
	InputController inputController(glfwGetCurrentContext(), sceneManager);

	while (!glfwWindowShouldClose(glfwGetCurrentContext())) {
		float currentFrame = glfwGetTime();
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		Scene* currentScene = sceneManager->getCurrentScene();
		currentScene->render();
		inputController.processInput(deltaTime);
		glfwSwapBuffers(glfwGetCurrentContext());
		glfwPollEvents();
	}
}

Application::~Application() {
	delete sceneManager;
	glfwTerminate();
}
