#ifndef TIL_INSTALLATION_H
#define TIL_INSTALLATION_H

#include <EEPROM.h>
#include <assert.h>
#include <controller/TimeBasedController.h>
#include <data/osc/OSCDataRouter.h>
#include <data/eeprom/EEPROMStorage.h>
#include "model/Slice.h"
#include "EEPROM.h"
#include "model/AppSettings.h"

#define EEPROM_SIZE 0x400
#define EEPROM_SETTINGS_ADDRESS 0x000
#define EEPROM_STATS_ADDRESS 0x300

typedef Slice *SlicePtr;

class Installation : public TimeBasedController {
private:
    SlicePtr *slices;

    uint16_t size;

    AppSettings *settings;

    Timer *autoSaveTimer;

    OSCDataRouter *oscDataRouter;

    EEPROMStorage *settingsStorage;

    EEPROMStorage *statsStorage;

    unsigned long lastSaveTimeStamp = 0;

public:
    Installation(uint16_t size, SlicePtr *portals, OSCDataRouter *oscDataRouter);

    void timedLoop() override;

    uint16_t getSize();

    SlicePtr *getSlices();

    SlicePtr getSlice(uint16_t index);

    SlicePtr getSlice(int index);

    void initSlices();

    void loadFromEEPROM();

    void saveToEEPROM();

    void loadDefaultSettings();

    void turnOn();

    void turnOff();

    AppSettings *getSettings();

    void resetStats();

    void saveStats();

    void loadStats();
};


#endif //TIL_INSTALLATION_H
