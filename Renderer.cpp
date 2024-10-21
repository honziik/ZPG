// Renderer.cpp
#include "Renderer.h"

Renderer::Renderer() {
    shader = new Shader(
        "#version 330 core\n"
        "layout(location = 0) in vec3 position;\n"
        "void main() {\n"
        "    gl_Position = vec4(position, 1.0);\n"
        "}",

        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 color;\n"
        "void main() {\n"
        "    FragColor = color;\n"
        "}"
    );

    shader2 = new Shader(
        "#version 330 core\n"
        "layout(location = 0) in vec3 position;\n"
        "void main() {\n"
        "    gl_Position = vec4(position, 1.0);\n"
        "}",

        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "    FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
        "}"
    );

    Triangle* triangle1 = new Triangle();
    float vertices1[] = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f
    };
    triangle1->setVertices(vertices1, sizeof(vertices1));
    triangle1->setColor(1.0f, 0.0f, 0.0f, 1.0f);
    models.push_back(triangle1); 

    Triangle* triangle2 = new Triangle();
    float vertices2[] = {
        0.7f, 0.7f, 0.0f,
        0.5f, 0.7f, 0.0f,
        0.7f, 0.6f, 0.0f
    };
    triangle2->setVertices(vertices2, sizeof(vertices2));
    triangle2->setColor(0.0f, 1.0f, 0.0f, 1.0f);
    models.push_back(triangle2);

    Triangle* triangle3 = new Triangle();
    float vertices3[] = {
        0.5f, 0.7f, 0.0f,
        0.7f, 0.6f, 0.0f,
        0.5f, 0.6f, 0.0f
    };
    triangle3->setVertices(vertices3, sizeof(vertices3));
    triangle3->setColor(0.0f, 0.0f, 1.0f, 1.0f);
    models.push_back(triangle3);

    Square* square1 = new Square();
    float squareVertices[] = {
       -0.9f, 0.5f, 0.0f,
        -0.25f, 0.5f, 0.0f,
       -0.9f, 0.0f, 0.0f,
        -0.25f, 0.0f, 0.0f
    };
    square1->setVertices(squareVertices, sizeof(squareVertices));
    square1->setColor(0.0f, 1.0f, 0.0f, 1.0f);
    models.push_back(square1);
}

void Renderer::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (Model* model : models) {
        if (dynamic_cast<Triangle*>(model)) {
            shader->use(); 
        }
        else {
            shader->use();
        }
        model->draw(shader->getProgram());
    }
}

Renderer::~Renderer() {
    delete shader;
    for (Model* model : models) {
        delete model;
    }
}
