//
// Created by Florian Bruggisser on 22.10.18.
//

#include <util/MathUtils.h>
#include "WaveScene.h"

WaveScene::WaveScene(Installation *installation) : BaseScene("WaveScene", installation) {
}

void WaveScene::setup() {
    BaseScene::setup();

    // reset waves
    for (unsigned long &wave : waves) {
        wave = 0UL;
    }
}

void WaveScene::loop() {
    BaseScene::loop();

    // update current waves
    for (unsigned long &waveStart : this->waves) {
        // check if is relevant
        if (waveStart == 0)
            continue;

        // calculate timediff
        auto timeDiff = millis() - waveStart;

        // update slices
        auto waveIsRelevant = false;
        for (auto i = 0; i < installation->getSize(); i++) {
            auto slice = installation->getSlice(i);

            if (updateSlice(slice, i, timeDiff))
                waveIsRelevant = true;
        }

        // stop wave if necessary
        if (!waveIsRelevant)
            waveStart = 0UL;
    }
}

bool WaveScene::updateSlice(SlicePtr slice, int sliceId, unsigned long timeDiff) {
    // do nothing till nmt relevant
    auto ldiff = timeDiff - (sliceId * installation->getSettings()->getWaveTravelSpeed());

    // wave relevant but not yet
    if (ldiff < 0L)
        return true;

    float x = ldiff / (float) installation->getSettings()->getWaveDuration();

    // wave not relevant anymore
    if (x > 1.0f) {
        return false;
    }

    // get brightness and update
    float brightness = MathUtils::windowedSine(x);
    float clamped = MathUtils::mapFromLEDBrightness(brightness, installation->getSettings()->getWaveMinBrightness(),
                                                    installation->getSettings()->getWaveMaxBrightness());
    slice->getLed()->setBrightness(clamped);
    return true;
}

void WaveScene::startWave() {
    waves[nextWaveIndex] = millis();
    nextWaveIndex = static_cast<uint8_t>((nextWaveIndex + 1) % MAX_WAVES);
}
