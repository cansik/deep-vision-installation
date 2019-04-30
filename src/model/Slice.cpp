//
// Created by Florian on 27.11.17.
//

#include <HardwareSerial.h>
#include "Slice.h"

Slice::Slice(unsigned short id) {
    this->id = id;
    this->led = new Led();
}

void Slice::update() {
    led->update();
}

unsigned short Slice::getId() {
    return id;
}

void Slice::turnOn() {
    led->turnOn(true);
}

void Slice::turnOff() {
    led->turnOff(true);
}

LedPtr Slice::getLed() {
    return led;
}