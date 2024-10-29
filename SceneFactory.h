#pragma once
#include "Scene.h"
#include "Translate.cpp"
#include "Scale.cpp"
#include "Rotate.cpp"
#include "CompositTransform.cpp"
class SceneFactory
{
public:
	static Scene* createFirstScene(Camera* camera);
	static Scene* createSecondScene(Camera* camera);
	static Scene* createThirdScene(Camera* camera);
	static Scene* createFourthScene(Camera* camera);
};

