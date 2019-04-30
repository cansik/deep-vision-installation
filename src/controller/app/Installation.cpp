//
// Created by Florian on 30.11.17.
//

#include "Installation.h"
#include "util/MathUtils.h"

Installation::Installation(uint16_t size, SlicePtr *portals, OSCDataRouter *oscDataRouter) :
        TimeBasedController(APP_FRAME_RATE, FRAMES_PER_SECOND) {

    this->size = size;
    this->slices = portals;
    this->oscDataRouter = oscDataRouter;

    this->settingsStorage = new EEPROMStorage(EEPROM_SETTINGS_ADDRESS, EEPROM_SIZE);
    this->statsStorage = new EEPROMStorage(EEPROM_STATS_ADDRESS, EEPROM_SIZE);

    this->settings = new AppSettings(oscDataRouter, settingsStorage, statsStorage);
    this->autoSaveTimer = new Timer(settings->getAutoSaveTime());
}

uint16_t Installation::getSize() {
    return size;
}

SlicePtr *Installation::getSlices() {
    return slices;
}

SlicePtr Installation::getSlice(uint16_t index) {
    assert(index >= 0 && index < size);
    return slices[index];
}

SlicePtr Installation::getSlice(int index) {
    return getSlice(static_cast<uint16_t>(index));
}

void Installation::initSlices() {
    for (uint8_t i = 0; i < size; i++) {
        slices[i] = new Slice(i);
    }
}

void Installation::turnOn() {
    for (auto i = 0; i < size; i++) {
        slices[i]->getLed()->setBrightness(1.0f);
    }
}

void Installation::turnOff() {
    for (auto i = 0; i < size; i++) {
        slices[i]->getLed()->setBrightness(0.0f);
    }
}

void Installation::loadFromEEPROM() {
    settingsStorage->load();
    Serial.printf("Loaded Version: %d\n", settings->getVersion());

    // check version and set default if needed
    if (settings->getVersion() != SETTINGS_VERSION) {
        Serial.println("applying default app settings!");
        settingsStorage->loadDefault();
    }
}

void Installation::saveToEEPROM() {
    settingsStorage->save();
}

void Installation::loadDefaultSettings() {
    settingsStorage->loadDefault();
}

void Installation::timedLoop() {
    TimeBasedController::timedLoop();

    // update slices
    for (auto i = 0; i < getSize(); i++) {
        getSlice(i)->update();
    }

    // auto save stats
    this->autoSaveTimer->setWaitTime(settings->getAutoSaveTime());
    if (settings->isAutoSave() && autoSaveTimer->elapsed()) {
        statsStorage->save();
        Serial.println("auto saved statistics");
    }
}

AppSettings *Installation::getSettings() {
    return settings;
}

void Installation::resetStats() {
    statsStorage->loadDefault();
    statsStorage->save();
}

void Installation::saveStats() {
    statsStorage->save();
}

void Installation::loadStats() {
    statsStorage->load();
}
