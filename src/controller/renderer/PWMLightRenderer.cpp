#include <cmath>

//
// Created by Florian Bruggisser on 21.10.18.
//

#include <esp_task_wdt.h>
#include <model/light/Led.h>
#include "PWMLightRenderer.h"
#include "../../util/MathUtils.h"
#include <analogWrite.h>

PWMLightRenderer::PWMLightRenderer(uint32_t pwmResolution, uint32_t pwmFrequency, uint8_t *pwmPins,
                                   Installation *installation)
        : LightRenderer(installation, installation->getSettings()->getAppFrameRate()) {
    this->pwmResolution = pwmResolution;
    this->pwmFrequency = pwmFrequency;
    this->pwmPins = pwmPins;

    // calculate max value
    pwmMaxValue = powl(2, pwmResolution) - 1;
}

void PWMLightRenderer::setup() {
    LightRenderer::setup();

    // set output options
    for (int i = 0; i < installation->getSize(); i++) {
        auto pinAddress = pwmPins[installation->getSlice(i)->getId()];

        analogWriteResolution(pinAddress, pwmResolution);
        analogWriteFrequency(pinAddress, pwmFrequency);
    }
}

void PWMLightRenderer::timedLoop() {
    LightRenderer::timedLoop();
}

void PWMLightRenderer::render(SlicePtr slice) {
    LightRenderer::render(slice);

    // get address => + 1 because buffer starts at 1 not 0
    auto pinAddress = pwmPins[slice->getId()];

    // map global brightness
    auto brightness = mapToGlobalBrightnessRange(slice->getLed()->getBrightness());

    // convert to dmx
    auto pwmValue = static_cast<uint8_t>(std::lround(
            MathUtils::map(brightness, LED_MIN_BRIGHTNESS, LED_MAX_BRIGHTNESS, pwmMinValue, pwmMaxValue)
    ));

    analogWrite(pinAddress, pwmValue, pwmMaxValue);
}
