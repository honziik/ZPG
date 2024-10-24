#include "SceneManager.h"
SceneManager::SceneManager() : currentSceneIndex(0) {}

void SceneManager::addScene(Scene* scene) {
    scenes.push_back(scene);
}

void SceneManager::switchScene() {
    if (currentSceneIndex + 1 >= scenes.size()){
        currentSceneIndex = 0;
    }else {
        currentSceneIndex += 1;
    }
}

Scene* SceneManager::getCurrentScene() {
    return scenes[currentSceneIndex];
}