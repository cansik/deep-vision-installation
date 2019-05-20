//
// Created by Florian Bruggisser on 2019-05-20.
//

#ifndef DEEP_VISION_INSTALLATION_FPSMONITOR_H
#define DEEP_VISION_INSTALLATION_FPSMONITOR_H


#include <controller/BaseController.h>

#define AVERAGE_ALPHA 0.1
#define MEASURE_TIME_SPAN 1000

class FPSMonitor : public BaseController {
private:
    bool isFirstMeasurement = true;

    float averageFPS = 0.0f;

    unsigned int frameCount = 0;
    unsigned long measureTimeStamp = 0;

    void updateAverage(unsigned int value);

public:
    virtual void setup() override;

    virtual void loop() override;

    float getAverageFps() const;
};


#endif //DEEP_VISION_INSTALLATION_FPSMONITOR_H
