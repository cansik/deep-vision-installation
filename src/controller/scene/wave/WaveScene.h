//
// Created by Florian Bruggisser on 22.10.18.
//

#ifndef TIL_WAVESCENE_H
#define TIL_WAVESCENE_H

#include "../BaseScene.h"
#include "../../app/Installation.h"

#define MAX_WAVES 10

class WaveScene : public BaseScene {
private:
    unsigned long waves[MAX_WAVES];
    int nextWaveIndex = 0;

    bool updateSlice(SlicePtr slice, int sliceId, unsigned long timeDiff);

public:
    explicit WaveScene(Installation *installation);

    void setup() override;

    void loop() override;

    void pollNewWave();

    void startWave();
};


#endif //TIL_WAVESCENE_H
