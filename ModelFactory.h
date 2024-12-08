#pragma once
#include "Models.h"
#include "CompositTransform.cpp"
#include <vector>
#include "Transform.h"
#include "ShaderProgram.h"
#include "Texture.h"
class ModelFactory
{
public:
	static Models* createModel(const float* vertices, int vertexCount,ShaderProgram* shader, std::vector<Transform*> transforms);
	static Models* createModelWithTexture(const float* vertices, int vertexCount, ShaderProgram* shader, std::vector<Transform*> transforms, const std::string& textureFilePath);
	static Models* createModelFromObject(const std::string& objectFilePath, const std::string& textureFilePath, ShaderProgram* shader, std::vector<Transform*> transforms);
};

