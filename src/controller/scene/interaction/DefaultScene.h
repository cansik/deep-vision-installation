//
// Created by Florian Bruggisser on 25.10.18.
//

#ifndef TIL_TIMESTARSCENE_H
#define TIL_TIMESTARSCENE_H


#include <controller/scene/star/TimeStar.h>
#include "../BaseScene.h"

class DefaultScene : public BaseScene {
private:

public:
    explicit DefaultScene(Installation *installation);

    void setup() override;

    void loop() override;

    void reset() override;
};


#endif //TIL_TIMESTARSCENE_H
