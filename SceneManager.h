#pragma once
#include <vector>
#include "Scene.h"

class SceneManager
{
    public:
        SceneManager();
        void addScene(Scene* scene);
        void switchScene(); 
        Scene* getCurrentScene();         

    private:
        std::vector<Scene*> scenes;  
        int currentSceneIndex;
};

