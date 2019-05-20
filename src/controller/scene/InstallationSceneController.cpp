//
// Created by Florian on 04.12.17.
//

#include "InstallationSceneController.h"
#include "SceneController.h"

InstallationSceneController::InstallationSceneController(Installation *installation, BaseScene *defaultScene) :
        SceneController(installation, defaultScene) {
    this->defaultScene = defaultScene;
}

void InstallationSceneController::setup() {
    SceneController::setup();
}

void InstallationSceneController::timedLoop() {
    SceneController::timedLoop();
}