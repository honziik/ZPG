#include "Scene.h"
#include <iostream>
#include "Tree.h"
#include "Bushes.h"
#include "CompositTransform.cpp"
#include "Translate.cpp"
#include "Scale.cpp"
#include "Rotate.cpp"

Scene::Scene(Camera* camera) {
    this->camera = camera;
    ShaderProgram* barevny = new ShaderProgram(
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

    ShaderProgram* zeleny = new ShaderProgram(
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
        "frag_colour = vec4(0.4f,0.5f,0.12f, 1.0);  // RED shader\n"
        "}\n",
        camera
    );

    shaders.push_back(barevny);
    shaders.push_back(zeleny);

    GLint idModelTransform = barevny->getUniformLocation("modelMatrix");
    if (idModelTransform == -1) {
        std::cerr << "Warning: uniform 'modelMatrix' not found in shader." << std::endl;
    }
    
    for (int i = 0; i < 50; ++i) {
        Models* treeModel = new Models(tree, 92814, true);
        treeModel->setShaderProgram(barevny);

        CompositeTransform* treeTransform = new CompositeTransform();

        float x = static_cast<float>(rand() % 100 - 50); // náhodné x mezi -50 a 50
        float z = static_cast<float>(rand() % 100 - 50); // náhodné z mezi -50 a 50
        treeTransform->addTransform(new Translate(glm::vec3(x, 0.0f, z)));

        float size = fmod(x, 4.0f); // Zbytek po dìlení 4
        if (size < 0) size *= -1;   // Zajistit, že velikost je kladná
        size = std::max(size, 4.5f); // Zajistit minimální velikost (napø. 0.5)

        treeTransform->addTransform(new Scale(glm::vec3(size, size, size))); 

        treeModel->setTransform(treeTransform);
        addObject(treeModel);
    }

    for (int i = 0; i < 50; ++i) {
        Models* bushModel = new Models(bushes, 8730, true);
        bushModel->setShaderProgram(zeleny);

        CompositeTransform* bushTransform = new CompositeTransform();

        float x = static_cast<float>(rand() % 100 - 50); // náhodné x mezi -50 a 50
        float z = static_cast<float>(rand() % 100 - 50); // náhodné z mezi -50 a 50
        bushTransform->addTransform(new Translate(glm::vec3(x, 0.0f, z)));

        float size = fmod(x, 3.0f); // Zbytek po dìlení 3 (pro keøe)
        if (size < 0) size *= -1;   // Zajistit, že velikost je kladná
        size = std::max(size, 4.5f); // Zajistit minimální velikost (napø. 0.5)

        bushTransform->addTransform(new Scale(glm::vec3(size, size, size))); // Velikost keøe se mìní podle x

        bushModel->setTransform(bushTransform);
        addObject(bushModel);
    }

}

void Scene::addObject(DrawableObject* object) {
    objects.push_back(object);
}

void Scene::init()
{
    for (ShaderProgram* shaderProgram : shaders) {
        camera->addObserver(shaderProgram);
    }
}

void Scene::render() {
 
    float aspectRatio = 1600.0f / 1200.0f;
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

    for (DrawableObject* object : objects) {
        glm::mat4 modelMatrix = object->getModelMatrix();
        object->getShaderProgram()->use();
        object->getShaderProgram()->setUniformMatrix4fv("modelMatrix", glm::value_ptr(modelMatrix));
        camera->notifyObservers();
        object->getShaderProgram()->setUniformMatrix4fv("projectionMatrix", glm::value_ptr(projectionMatrix));
       
        object->draw();
    }
}