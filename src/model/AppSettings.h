//
// Created by Florian Bruggisser on 29.10.18.
//

#ifndef TIL_APPSETTINGS_H
#define TIL_APPSETTINGS_H

#include <data/osc/OSCDataRouter.h>
#include <data/eeprom/EEPROMStorage.h>
#include <data/model/DataModel.h>
#include <data/model/ArrayDataModel.h>
#include "DeepVisionConstants.h"

#define SETTINGS_VERSION 1000

#define APP_FRAME_RATE 60L

class AppSettings {
private:
    DataModel<int> version = DataModel<int>(SETTINGS_VERSION);

    // global render settings
    DataModel<unsigned long> appFrameRate = DataModel<unsigned long>(APP_FRAME_RATE);

    DataModel<float> minBrightness = DataModel<float>(0.0f);

    DataModel<float> maxBrightness = DataModel<float>(1.0f);

    DataModel<bool> gammaCorrection = DataModel<bool>(true);

    DataModel<bool> autoSave = DataModel<bool>(true);

    DataModel<unsigned long> autoSaveTime = DataModel<unsigned long>(30 * 60 * 1000);

    // stats
    DataModel<unsigned long> runningTime = DataModel<unsigned long>(0);

    DataModel<unsigned int> restartCount = DataModel<unsigned int>(0);

    // time star scene settings
    DataModel<unsigned long> timeStarMinDuration = DataModel<unsigned long>(1500L); // used for portal scene as timer

    DataModel<unsigned long> timeStarMaxDuration = DataModel<unsigned long>(5000L);

    DataModel<float> timeStarRandomOnFactor = DataModel<float>(0.99f);

    DataModel<float> timeStarMinBrightness = DataModel<float>(0.4f);

    DataModel<float> timeStarMaxBrightness = DataModel<float>(0.8f);

    // show settings
    DataModel<unsigned long> showSpeed = DataModel<unsigned long>(1000L);

    DataModel<bool> sceneControllerOn = DataModel<bool>(true);

    // brightness
    ArrayDataModel<float> defaultBrightness = ArrayDataModel<float>(1.0, SLICE_COUNT);

public:
    AppSettings(OSCDataRouter *oscDataRouter, EEPROMStorage *eepromStorage, EEPROMStorage *statsStorage);

    int getVersion() const;

    unsigned long getAppFrameRate() const;

    unsigned long getRunningTime() const;

    void setRunningTime(unsigned long value);

    void incRunningTime(unsigned long value);

    unsigned int getRestartCount() const;

    void setRestartCount(unsigned int value);

    void incRestartCount();

    float getMinBrightness() const;

    void setMinBrightness(float minBrightness);

    float getMaxBrightness() const;

    void setMaxBrightness(float maxBrightness);

    bool isGammaCorrection() const;

    void setGammaCorrection(bool gammaCorrection);

    unsigned long getTimeStarMinDuration() const;

    void setTimeStarMinDuration(unsigned long timeStarMinDuration);

    unsigned long getTimeStarMaxDuration() const;

    void setTimeStarMaxDuration(unsigned long timeStarMaxDuration);

    float getTimeStarRandomOnFactor() const;

    void setTimeStarRandomOnFactor(float timeStarRandomOnFactor);

    float getTimeStarMinBrightness() const;

    void setTimeStarMinBrightness(float timeStarMinBrightness);

    float getTimeStarMaxBrightness() const;

    void setTimeStarMaxBrightness(float timeStarMaxBrightness);

    unsigned long getShowSpeed() const;

    void setShowSpeed(unsigned long showSpeed);

    bool isAutoSave() const;

    void setAutoSave(bool autoSave);

    unsigned long getAutoSaveTime() const;

    void setAutoSaveTime(unsigned long autoSaveTime);

    const bool isSceneControllerOn() const;

    void setSceneControllerOn(bool value);

    const float getDefaultBrightness(int index) const;
};


#endif //TIL_APPSETTINGS_H
