//
// Created by Florian on 09.10.18.
//

#ifndef TIL_SERIALLIGHTRENDERER_H
#define TIL_SERIALLIGHTRENDERER_H


#include "LightRenderer.h"
#include "../../util/StopWatch.h"
#include "../../util/Timer.h"

#define SERIAL_RENDER_FRAMERATE 60

class SerialLightRenderer : public LightRenderer {
private:
    StopWatch watch = StopWatch();

public:
    explicit SerialLightRenderer(Installation *installation);

    void setup() override;

    void timedLoop() override;

    void render(SlicePtr portal) override;
};


#endif //TIL_SERIALLIGHTRENDERER_H
