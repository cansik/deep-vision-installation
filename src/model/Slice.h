//
// Created by Florian on 27.11.17.
//

#ifndef SILVA_LEAF_H
#define SILVA_LEAF_H

#include <model/light/RGBLed.h>
#include <util/Timer.h>
#include "../util/EasingValue.h"

typedef Led *LedPtr;

class Slice {
private:
    unsigned short id;

    LedPtr led;

public:
    explicit Slice(unsigned short id);

    void update();

    unsigned short getId();

    void turnOn();

    void turnOff();

    LedPtr getLed();
};


#endif //SILVA_LEAF_H
