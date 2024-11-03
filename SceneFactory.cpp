#include "SceneFactory.h"
#include "Tree.h"
#include "Bushes.h"
#include "Square.h"
#include "Sphere.h"
#include "Light.h"

Scene* SceneFactory::createFirstScene()
{
    Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
    Scene* scene = new Scene(camera);

    ShaderProgram* triangleShader = new ShaderProgram(
        "#version 330 core\n"
        "layout(location = 0) in vec3 vp;  // Vertex position\n"
        "layout(location = 1) in vec3 vn;  // Vertex normal\n"

        "out vec3 fragPos;   // Fragment position (to pass to fragment shader)\n"
        "out vec3 fragNormal;  // Normal (to pass to fragment shader)\n"

        "uniform mat4 modelMatrix;      // Model transformation matrix\n"
        "uniform mat4 viewMatrix;       // View (camera) transformation matrix\n"
        "uniform mat4 projectionMatrix; // Projection matrix (perspective or orthographic)\n"

        "void main() {\n"
        "fragNormal = mat3(transpose(inverse(modelMatrix))) * vn;  // Transform normal to world space\n"
        "   fragPos = vec3(modelMatrix * vec4(vp, 1.0));  // Transform vertex position to world space\n"
        "   gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);  // Final transformed position\n"
        "}\n"
        ,

        "#version 330 core\n"

        "in vec3 fragNormal;  // Normal from vertex shader\n"
        "in vec3 fragPos;     // Position from vertex shader\n"

        "out vec4 frag_colour;  // Output color\n"

        "void main() {\n"
        "frag_colour = vec4(0.164f,0.042f,0.042f, 1.0);  \n"
        "}\n",
        camera
    );

    scene->addShader(triangleShader);


    Models* triangleModel = new Models(square, 6, false);
    triangleModel->setShaderProgram(triangleShader);
    scene->addObject(triangleModel);
    scene->init();

    return scene;
}

Scene* SceneFactory::createSecondScene()
{
    Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);

    Scene* scene = new Scene(camera);

    ShaderProgram* colorful = new ShaderProgram(
        "#version 330 core\n"
        "layout(location = 0) in vec3 vp;  // Vertex position\n"
        "layout(location = 1) in vec3 vn;  // Vertex normal\n"

        "out vec3 fragPos;   // Fragment position (to pass to fragment shader)\n"
        "out vec3 fragNormal;  // Normal (to pass to fragment shader)\n"

        "uniform mat4 modelMatrix;      // Model transformation matrix\n"
        "uniform mat4 viewMatrix;       // View (camera) transformation matrix\n"
        "uniform mat4 projectionMatrix; // Projection matrix (perspective or orthographic)\n"

        "void main() {\n"
        "fragNormal = mat3(transpose(inverse(modelMatrix))) * vn;  // Transform normal to world space\n"
        "   fragPos = vec3(modelMatrix * vec4(vp, 1.0));  // Transform vertex position to world space\n"
        "   gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);  // Final transformed position\n"
        "}\n"
        ,

        "#version 330 core\n"

        "in vec3 fragNormal;  // Normal from vertex shader\n"
        "in vec3 fragPos;     // Position from vertex shader\n"

        "out vec4 frag_colour;  // Output color\n"

        "void main() {\n"
        "vec3 color = normalize(fragNormal) * 0.5 + 0.5;  // Simple shading\n"
        "frag_colour = vec4(color, 1.0);\n"
        "}\n",
        camera
    );

    ShaderProgram* green = new ShaderProgram(
        "#version 330 core\n"
        "layout(location = 0) in vec3 vp;  // Vertex position\n"
        "layout(location = 1) in vec3 vn;  // Vertex normal\n"

        "out vec3 fragPos;   // Fragment position (to pass to fragment shader)\n"
        "out vec3 fragNormal;  // Normal (to pass to fragment shader)\n"

        "uniform mat4 modelMatrix;      // Model transformation matrix\n"
        "uniform mat4 viewMatrix;       // View (camera) transformation matrix\n"
        "uniform mat4 projectionMatrix; // Projection matrix (perspective or orthographic)\n"

        "void main() {\n"
        "fragNormal = mat3(transpose(inverse(modelMatrix))) * vn;  // Transform normal to world space\n"
        "   fragPos = vec3(modelMatrix * vec4(vp, 1.0));  // Transform vertex position to world space\n"
        "   gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);  // Final transformed position\n"
        "}\n"
        ,

        "#version 330 core\n"

        "in vec3 fragNormal;  // Normal from vertex shader\n"
        "in vec3 fragPos;     // Position from vertex shader\n"

        "out vec4 frag_colour;  // Output color\n"

        "void main() {\n"
        "frag_colour = vec4(0.4f,0.5f,0.12f, 1.0);  \n"
        "}\n",
        camera
    );

    ShaderProgram* brown = new ShaderProgram(
        "#version 330 core\n"
        "layout(location = 0) in vec3 vp;  // Vertex position\n"
        "layout(location = 1) in vec3 vn;  // Vertex normal\n"

        "out vec3 fragPos;   // Fragment position (to pass to fragment shader)\n"
        "out vec3 fragNormal;  // Normal (to pass to fragment shader)\n"

        "uniform mat4 modelMatrix;      // Model transformation matrix\n"
        "uniform mat4 viewMatrix;       // View (camera) transformation matrix\n"
        "uniform mat4 projectionMatrix; // Projection matrix (perspective or orthographic)\n"

        "void main() {\n"
        "fragNormal = mat3(transpose(inverse(modelMatrix))) * vn;  // Transform normal to world space\n"
        "   fragPos = vec3(modelMatrix * vec4(vp, 1.0));  // Transform vertex position to world space\n"
        "   gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);  // Final transformed position\n"
        "}\n"
        ,

        "#version 330 core\n"

        "in vec3 fragNormal;  // Normal from vertex shader\n"
        "in vec3 fragPos;     // Position from vertex shader\n"

        "out vec4 frag_colour;  // Output color\n"

        "void main() {\n"
        "frag_colour = vec4(0.164f,0.042f,0.042f, 1.0);  \n"
        "}\n",
        camera
    );

    scene->addShader(colorful);
    scene->addShader(green);
    scene->addShader(brown);


    GLint idModelTransform = colorful->getUniformLocation("modelMatrix");
    if (idModelTransform == -1) {
        std::cerr << "Warning: uniform 'modelMatrix' not found in shader." << std::endl;
    }

    for (int i = 0; i < 50; ++i) {
        Models* treeModel = new Models(tree, 92814, true);
        treeModel->setShaderProgram(colorful);

        CompositeTransform* treeTransform = new CompositeTransform();

        float x = static_cast<float>(rand() % 100 - 50);
        float z = static_cast<float>(rand() % 100 - 50);
        treeTransform->addTransform(new Translate(glm::vec3(x, 0.0f, z)));

        float size = 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (2.0f)));

        treeTransform->addTransform(new Scale(glm::vec3(size, size, size)));

        treeModel->setTransform(treeTransform);
        scene->addObject(treeModel);
    }

    for (int i = 0; i < 50; ++i) {
        Models* bushModel = new Models(bushes, 8730, true);
        bushModel->setShaderProgram(green);

        CompositeTransform* bushTransform = new CompositeTransform();

        float x = static_cast<float>(rand() % 100 - 50);
        float z = static_cast<float>(rand() % 100 - 50);
        bushTransform->addTransform(new Translate(glm::vec3(x, 0.0f, z)));

        float size = 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (3.0f)));

        bushTransform->addTransform(new Scale(glm::vec3(size, size, size)));

        bushModel->setTransform(bushTransform);
        scene->addObject(bushModel);
    }

    Models* grass = new Models(square, 6, true);
    grass->setShaderProgram(brown);

    scene->addObject(grass);
    scene->init();

    return scene;
}

Scene* SceneFactory::createThirdScene()
{
    Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
    Scene* scene = new Scene(camera);

    ShaderProgram* colorful = new ShaderProgram(
        "#version 330 core\n"
        "layout(location = 0) in vec3 vp;  // Vertex position\n"
        "layout(location = 1) in vec3 vn;  // Vertex normal\n"

        "out vec3 fragPos;   // Fragment position (to pass to fragment shader)\n"
        "out vec3 fragNormal;  // Normal (to pass to fragment shader)\n"

        "uniform mat4 modelMatrix;      // Model transformation matrix\n"
        "uniform mat4 viewMatrix;       // View (camera) transformation matrix\n"
        "uniform mat4 projectionMatrix; // Projection matrix (perspective or orthographic)\n"

        "void main() {\n"
        "   fragNormal = mat3(transpose(inverse(modelMatrix))) * vn;  // Transform normal to world space\n"
        "   fragPos = vec3(modelMatrix * vec4(vp, 1.0));  // Transform vertex position to world space\n"
        "   gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);  // Final transformed position\n"
        "}\n"
        ,
        "#version 330 core\n"

        "in vec3 fragNormal;  // Normal from vertex shader\n"
        "in vec3 fragPos;     // Position from vertex shader\n"

        "out vec4 frag_colour;  // Output color\n"
        "uniform vec3 lightPosition; // Light position in world space\n"
        "uniform vec3 lightColor;    // Light color\n"

        "void main() {\n"
        "   // Ambient light component\n"
        "   vec3 ambient = 0.2 * lightColor;\n"

        "   // Diffuse light component\n"
        "   vec3 norm = normalize(fragNormal);\n"
        "   vec3 lightDir = normalize(lightPosition - fragPos);\n"
        "   float diff = max(dot(norm, lightDir), 0.0);\n"
        "   vec3 diffuse = diff * lightColor;\n"

        "   // Final color: ambient + diffuse with grey tone\n"
        "   vec3 resultColor = (ambient + diffuse) * vec3(0.5);  // grey color\n"
        "   frag_colour = vec4(resultColor, 1.0);\n"
        "}\n",
        camera
    );
    scene->addShader(colorful);

    GLint idModelTransform = colorful->getUniformLocation("modelMatrix");
    if (idModelTransform == -1) {
        std::cerr << "Warning: uniform 'modelMatrix' not found in shader." << std::endl;
    }

    Light* light = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f));
    light->addObserver(colorful);
    colorful->setLight(light);

    for (int i = 0; i < 4; ++i) {
        Models* treeModel = new Models(sphere, 2880, true);
        treeModel->setShaderProgram(colorful);

        CompositeTransform* treeTransform = new CompositeTransform();

        float x = (i % 2 == 0 ? -1.5f : 1.5f);
        float z = (i / 2 == 0 ? -1.5f : 1.5f);
        treeTransform->addTransform(new Translate(glm::vec3(x, 0.0f, z)));

        treeModel->setTransform(treeTransform);
        scene->addObject(treeModel);
    }
    scene->init();

    return scene;
}

Scene* SceneFactory::createFourthScene()
{
    return nullptr;
}
