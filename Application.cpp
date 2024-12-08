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
	sceneManager->getCurrentScene()->getCamera()->aspectRatio = aspectRatio;
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

	if (currentTime - lastSwitchTime < switchDelay) {
		return;
	}

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		currentScene->changeSkybox();
		lastSwitchTime = currentTime;

	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {

		lastSwitchTime = currentTime;

		if (cursorLocked) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		cursorLocked = !cursorLocked;

	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		sceneManager->switchScene();
		lastSwitchTime = currentTime;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		GLbyte color[4];
		GLfloat depth;
		GLuint index;
		lastSwitchTime = currentTime;
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		int newy = 1200 - y;

		glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

		//printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth % f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);

		sceneManager->getCurrentScene()->removeObject(index);
		glm::vec3 screenX = glm::vec3(x, newy, depth);
		glm::mat4 view = camera->getViewMatrix();
		glm::mat4 projection = camera->getProjectionMatrix();
		glm::vec4 viewPort = glm::vec4(0, 0, 1600, 1200);
		glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

		printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		GLbyte color[4];
		GLfloat depth;
		GLuint index;
		lastSwitchTime = currentTime;
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		int newy = 1200 - y;

		glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

		//printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth % f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);

		glm::vec3 screenX = glm::vec3(x, newy, depth);
		glm::mat4 view = camera->getViewMatrix();
		glm::mat4 projection = camera->getProjectionMatrix();
		glm::vec4 viewPort = glm::vec4(0, 0, 1600, 1200);
		glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

		sceneManager->getCurrentScene()->addObject(pos);
		printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);
	}

	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
		GLbyte color[4];
		GLfloat depth;
		GLuint index;
		lastSwitchTime = currentTime;
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		int newy = 1200 - y;

		glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

		//printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth % f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);

		glm::vec3 screenX = glm::vec3(x, newy, depth);
		glm::mat4 view = camera->getViewMatrix();
		glm::mat4 projection = camera->getProjectionMatrix();
		glm::vec4 viewPort = glm::vec4(0, 0, 1600, 1200);
		glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);
		sceneManager->getCurrentScene()->controlPoints.push_back(pos);
		printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);
	}
	
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		sceneManager->getCurrentScene()->addBObject();
	}
}

void APIENTRY openglDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	std::cerr << "OpenGL Debug Message: " << message << std::endl;
}

Application::Application() {
	cursorLocked = false;
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

	while (!glfwWindowShouldClose(glfwGetCurrentContext())) {
		float currentFrame = glfwGetTime();
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		Scene* currentScene = sceneManager->getCurrentScene();
		currentScene->render();
		processInput(glfwGetCurrentContext(), deltaTime);

		glfwSwapBuffers(glfwGetCurrentContext());
		glfwPollEvents();
	}
}

Application::~Application() {
	delete sceneManager;
	glfwTerminate();
}
