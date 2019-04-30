//
// Created by Florian on 04.12.17.
//

#ifndef SILVA_ABEN_CONTROLLER_H
#define SILVA_ABEN_CONTROLLER_H

#include "BaseScene.h"
#include "SceneController.h"

class InstallationSceneController : public SceneController {
private:
    BaseScene *defaultScene;

    BaseScene *showScene;

public:
    explicit InstallationSceneController(Installation *installation, BaseScene *defaultScene, BaseScene *showScene);

    void setup() override;

    void timedLoop() override;

    void selectRelevantScene();
};

#endif //SILVA_ABEN_CONTROLLER_H
