//
// Created by Florian Bruggisser on 2019-05-20.
//

#include <esp32-hal.h>
#include <HardwareSerial.h>
#include "FPSMonitor.h"

void FPSMonitor::setup() {
    BaseController::setup();

    measureTimeStamp = millis();
}

void FPSMonitor::loop() {
    BaseController::loop();

    // increase framecount
    frameCount++;

    auto timeStamp = millis();
    if (timeStamp - measureTimeStamp >= MEASURE_TIME_SPAN) {
        measureTimeStamp = timeStamp;

        if (isFirstMeasurement) {
            isFirstMeasurement = false;
            averageFPS = frameCount;
        }

        updateAverage(frameCount);
        frameCount = 0;

        Serial.printf("FPS: %f\n", getAverageFps());
    }
}

void FPSMonitor::updateAverage(unsigned int value) {
    averageFPS = (AVERAGE_ALPHA * value) + (1.0 - AVERAGE_ALPHA) * averageFPS;
}

float FPSMonitor::getAverageFps() const {
    return averageFPS;
}
