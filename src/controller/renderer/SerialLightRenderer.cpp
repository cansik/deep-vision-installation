//
// Created by Florian on 09.10.18.
//

#include <HardwareSerial.h>
#include "SerialLightRenderer.h"

SerialLightRenderer::SerialLightRenderer(Installation *installation)
        : LightRenderer(installation, SERIAL_RENDER_FRAMERATE) {

}

void SerialLightRenderer::setup() {
    LightRenderer::setup();

    watch.start();
}

void SerialLightRenderer::timedLoop() {
    LightRenderer::timedLoop();

    String msg = "SLR;";

    for (int i = 0; i < installation->getSize(); i++) {
        auto brightness = mapToGlobalBrightnessRange(installation->getSlice(i)->getLed()->getBrightness());

        msg += String(brightness) + ";";
    }

    msg += "\n";
    Serial.print(msg);
    Serial.flush();
}

void SerialLightRenderer::render(SlicePtr portal) {
    LightRenderer::render(portal);
}
