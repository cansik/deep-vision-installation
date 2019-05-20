//
// Created by Florian Bruggisser on 01.01.19.
//

#ifndef ABEN_SCALEBINDINGCONVERTER_H
#define ABEN_SCALEBINDINGCONVERTER_H


#include <data/osc/rule/converter/IOSCBindingConverter.h>

class ScaleBindingConverter : public IOSCBindingConverter {
private:
    float scale;
    bool roundValue;
    int decimalPlaces;

public:
    explicit ScaleBindingConverter(float scale, bool roundValue = false, int decimalPlaces = 0);

    float convertInput(float value) override;

    float convertOutput(float value) override;

    float getScale() const;

    void setScale(float scale);

    bool isRoundValue() const;

    void setRoundValue(bool roundValue);

    int getDecimalPlaces() const;

    void setDecimalPlaces(int decimalPlaces);
};


#endif //ABEN_SCALEBINDINGCONVERTER_H
