//
// Created by Florian on 04.12.17.
//

#include "InstallationSceneController.h"
#include "SceneController.h"

InstallationSceneController::InstallationSceneController(Installation *installation, BaseScene *defaultScene, BaseScene *showScene) :
        SceneController(installation, defaultScene) {
    this->defaultScene = defaultScene;
    this->showScene = showScene;
}

void InstallationSceneController::setup() {
    SceneController::setup();

    defaultScene->setup();
    showScene->setup();
}

void InstallationSceneController::timedLoop() {
    SceneController::timedLoop();
    selectRelevantScene();
}

void InstallationSceneController::selectRelevantScene() {
    // do not automatically switch scenes
}