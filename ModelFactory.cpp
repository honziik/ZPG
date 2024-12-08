#include "ModelFactory.h"

Models* ModelFactory::createModel(const float* vertices, int vertexCount,ShaderProgram* shader, std::vector<Transform*> transforms)
{
    Models* model = new Models(vertices, vertexCount, true, false);

    model->setShaderProgram(shader);

    CompositeTransform* transform = new CompositeTransform();
    for (Transform* t : transforms) {
        transform->addTransform(t);
    }
    model->transform = transform;

    return model;
}

Models* ModelFactory::createModelWithTexture(const float* vertices, int vertexCount, ShaderProgram* shader, std::vector<Transform*> transforms, const std::string& textureFilePath)
{
    Models* model = new Models(vertices, vertexCount, true, true);
    model->setShaderProgram(shader);
    Texture* texture = new Texture();
    texture->loadFromFile(textureFilePath);
    CompositeTransform* transform = new CompositeTransform();
    for (Transform* t : transforms) {
        transform->addTransform(t);
    }
    model->transform = transform;
    model->setTexture(texture);
    return model;
}

Models* ModelFactory::createModelFromObject(const std::string& objectFilePath, const std::string& textureFilePath, ShaderProgram* shader, std::vector<Transform*> transforms)
{
    Models* model = new Models(objectFilePath, textureFilePath);
    model->setShaderProgram(shader);
    CompositeTransform* transform = new CompositeTransform();
    for (Transform* t : transforms) {
        transform->addTransform(t);
    }
    model->transform = transform;
    return model;
}
