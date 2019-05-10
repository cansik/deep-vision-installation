//
// Created by Florian Bruggisser on 25.10.18.
//

#ifndef DV_TIMESTARSCENE_H
#define DV_TIMESTARSCENE_H


#include "../BaseScene.h"
#include "TimeStar.h"

class TimeStarScene : public BaseScene {
private:
    typedef TimeStar *TimeStarPtr;

    uint16_t starCount;

    TimeStarPtr *stars;

public:
    explicit TimeStarScene(Installation *installation);

    void setup() override;

    void loop() override;

    void resetStar(int id);
};


#endif //DV_TIMESTARSCENE_H
