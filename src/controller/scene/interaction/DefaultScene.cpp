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
        auto slice = installation->getSlice(i);

        // update brightness (let it shine)
        auto brightness = installation->getSettings()->getDefaultBrightness(i);
        slice->getLed()->setBrightness(brightness);
    }
}

void DefaultScene::reset() {
    BaseScene::reset();
}
