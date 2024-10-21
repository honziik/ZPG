#include "Scene.h"
#include <iostream>
#include "Tree.h"
#include "Bushes.h"
#include "CompositTransform.cpp"
#include "Translate.cpp"
#include "Scale.cpp"
#include "Rotate.cpp"

Scene::Scene() {
   /*       basic shader :D
   ShaderProgram* shader1 = new ShaderProgram(
        "#version 330 core\n"
        "layout(location = 0) in vec3 position;\n"
        "void main() {\n"
        "    gl_Position =  vec4(position, 1.0);\n"
        "}",
        "#version 330\n"
        "out vec4 frag_colour;"
        "void main () {"
        "     frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
        "}"
    );*/


    ShaderProgram* shader2 = new ShaderProgram(
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
        "}\n"
    );

    ShaderProgram* shader3 = new ShaderProgram(
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
        "}\n"
    );

    GLint idModelTransform = shader2->getUniformLocation("modelMatrix");
    if (idModelTransform == -1) {
        std::cerr << "Warning: uniform 'modelMatrix' not found in shader." << std::endl;
    }
    
    Models* model = new Models(tree, 92814, true);
    model->setShaderProgram(shader2);

    Models* model2 = new Models(bushes, 8730, true);
    model2->setShaderProgram(shader3);

    Models* model3 = new Models(bushes, 8730, true);
    model3->setShaderProgram(shader2);

    CompositeTransform* compositeTransform1 = new CompositeTransform();
    compositeTransform1->addTransform(new Scale(glm::vec3(2.0f, 2.0f, 2.0f)));
    compositeTransform1->addTransform(new Translate(glm::vec3(-2.0f, 0.0f, 0.0f)));

    CompositeTransform* compositeTransform2 = new CompositeTransform();
    compositeTransform2->addTransform(new Rotate(20.0f, glm::vec3(1.0f, 0.0f, 0.0f)));
    compositeTransform2->addTransform(new Translate(glm::vec3(0.0f, 0.0f, 0.0f)));

    CompositeTransform* compositeTransform3 = new CompositeTransform();
    compositeTransform3->addTransform(new Rotate(-20.0f, glm::vec3(1.0f, 0.0f, 0.0f)));

    model2->setTransform(compositeTransform1);
    model->setTransform(compositeTransform2);
    model3->setTransform(compositeTransform3);

    addObject(model);
    addObject(model2);
    addObject(model3);


  /*Triangle* triangle = new Triangle();
    triangle->setShaderProgram(shader1);
    addObject(triangle);*/
}

void Scene::addObject(DrawableObject* object) {
    objects.push_back(object);
}

void Scene::setCamera(Camera* camera)
{
    this->camera = camera;
}

void Scene::render() {
    /*glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);  // Example camera position
    glm::vec3 cameraTarget = glm::vec3(0.0f, 3.0f, 0.0f);  // Look at the origin
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);  // Up vector

    glm::mat4 viewMatrix = glm::lookAt(cameraPos, cameraTarget, up);*/
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);  // Example camera position
    glm::vec3 cameraTarget = glm::vec3(0.0f, 3.0f, 0.0f);  // Look at the origin
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);  // Up vector
    glm::mat4 viewMatrix = glm::lookAt(cameraPos, cameraTarget, up);
    // Set up projection matrix (perspective)
    float aspectRatio = 800.0f / 600.0f;  // Example aspect ratio (screen width / height)
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
    for (DrawableObject* object : objects) {
        glm::mat4 modelMatrix = object->getModelMatrix();
        object->getShaderProgram()->setUniformMatrix4fv("modelMatrix", glm::value_ptr(modelMatrix));
        object->getShaderProgram()->setUniformMatrix4fv("viewMatrix", glm::value_ptr(viewMatrix));
        object->getShaderProgram()->setUniformMatrix4fv("projectionMatrix", glm::value_ptr(projectionMatrix));
        // Vykresli objekt
        object->draw();
    }
}