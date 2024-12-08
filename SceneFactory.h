#pragma once
#include "Scene.h"
#include "Translate.cpp"
#include "Scale.cpp"
#include "Rotate.cpp"
#include "ModelFactory.h"
#include <vector>
class SceneFactory
{
public:
	static Scene* createFirstScene();
	static Scene* createSecondScene();
	static Scene* createThirdScene();
	static Scene* createFourthScene();
	static Scene* createFifthScene();
};

