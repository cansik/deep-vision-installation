//
// Created by Florian Bruggisser on 21.10.18.
//

#ifndef TIL_DMXLIGHTRENDERER_H
#define TIL_DMXLIGHTRENDERER_H


#include "LightRenderer.h"

#define DMX_MAX_CHANNEL 512

#define DMX_MIN_VALUE 0
#define DMX_MAX_VALUE 255

class PWMLightRenderer : public LightRenderer {
private:
    uint8_t *pwmPins;
    uint32_t pwmResolution;
    uint32_t pwmFrequency;

    uint8_t pwmMinValue = 0;
    uint8_t pwmMaxValue;

public:
    explicit PWMLightRenderer(uint32_t pwmResolution, uint32_t pwmFrequency, uint8_t *pwmPins,
                              Installation *installation);

    void setup() override;

    void timedLoop() override;

    void render(SlicePtr slice) override;
};


#endif //TIL_DMXLIGHTRENDERER_H
