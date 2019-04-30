//
// Created by Florian Bruggisser on 25.10.18.
//

#include "DefaultScene.h"
#include "../../../util/MathUtils.h"

DefaultScene::DefaultScene(Installation *installation) : BaseScene(
        "DefaultScene", installation) {
}

void DefaultScene::setup() {
    BaseScene::setup();
}

void DefaultScene::loop() {
    BaseScene::loop();

    for (auto i = 0; i < installation->getSize(); i++) {
        auto portal = installation->getSlice(i);

        // update brightness (let it shine)
        portal->getLed()->setBrightness(LED_MAX_BRIGHTNESS);
    }
}

void DefaultScene::reset() {
    BaseScene::reset();
}
