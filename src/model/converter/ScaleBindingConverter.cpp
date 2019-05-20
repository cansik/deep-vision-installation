//
// Created by Florian Bruggisser on 01.01.19.
//

#include <Arduino.h>
#include <util/MathUtils.h>
#include "ScaleBindingConverter.h"

ScaleBindingConverter::ScaleBindingConverter(float scale, bool roundValue, int decimalPlaces) {
    this->scale = scale;
    this->roundValue = roundValue;
    this->decimalPlaces = decimalPlaces;
}


float ScaleBindingConverter::convertInput(float value) {
    auto result = value * scale;

    if (roundValue)
        return MathUtils::round(result, decimalPlaces);

    return result;
}

float ScaleBindingConverter::convertOutput(float value) {
    auto result = value / scale;

    if (roundValue)
        return MathUtils::round(result, decimalPlaces);

    return result;
}

float ScaleBindingConverter::getScale() const {
    return scale;
}

void ScaleBindingConverter::setScale(float scale) {
    ScaleBindingConverter::scale = scale;
}

bool ScaleBindingConverter::isRoundValue() const {
    return roundValue;
}

void ScaleBindingConverter::setRoundValue(bool roundValue) {
    ScaleBindingConverter::roundValue = roundValue;
}

int ScaleBindingConverter::getDecimalPlaces() const {
    return decimalPlaces;
}

void ScaleBindingConverter::setDecimalPlaces(int decimalPlaces) {
    ScaleBindingConverter::decimalPlaces = decimalPlaces;
}
