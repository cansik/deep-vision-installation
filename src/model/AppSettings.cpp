//
// Created by Florian Bruggisser on 29.10.18.
//

#include <data/osc/rule/OSCDataBinding.h>
#include <model/converter/ScaleBindingConverter.h>
#include "AppSettings.h"

AppSettings::AppSettings(OSCDataRouter *oscDataRouter, EEPROMStorage *eepromStorage, EEPROMStorage *statsStorage) {
    // eeprom
    eepromStorage->add(&sceneControllerOn);
    eepromStorage->add(&version);
    eepromStorage->add(&minBrightness);
    eepromStorage->add(&maxBrightness);
    eepromStorage->add(&gammaCorrection);
    eepromStorage->add(&autoSave);
    eepromStorage->add(&autoSaveTime);
    eepromStorage->add(&timeStarMinDuration);
    eepromStorage->add(&timeStarMaxDuration);
    eepromStorage->add(&timeStarRandomOnFactor);
    eepromStorage->add(&timeStarMinBrightness);
    eepromStorage->add(&timeStarMaxBrightness);
    eepromStorage->add(&showSpeed);
    eepromStorage->add(&defaultBrightness);

    // stats
    statsStorage->add(&runningTime);
    statsStorage->add(&restartCount);

    // create converter
    auto secondConverter = new ScaleBindingConverter(1000, true);
    auto minuteConverter = new ScaleBindingConverter(1000 * 60, true);
    auto hourConverter = new ScaleBindingConverter(1000 * 60 * 60, true);
    auto deciSecondConverter = new ScaleBindingConverter(10, true, 1);

    //auto dayConverter = new ScaleBindingConverter(1000 * 60 * 60 * 24, true);

    // osc
    oscDataRouter->addRule(new OSCDataBinding("/dv/version", &version, true));
    oscDataRouter->addRule(new OSCDataBinding("/dv/scenemanager/on", &sceneControllerOn, true));
    oscDataRouter->addRule(new OSCDataBinding("/dv/brightness/min", &minBrightness, true));
    oscDataRouter->addRule(new OSCDataBinding("/dv/brightness/max", &maxBrightness, true));
    oscDataRouter->addRule(new OSCDataBinding("/dv/gamma/on", &gammaCorrection, true));
    oscDataRouter->addRule(new OSCDataBinding("/dv/gamma/factor", &gammaFactor, true));

    oscDataRouter->addRule(new OSCDataBinding("/dv/autosave/on", &autoSave, true));
    oscDataRouter->addRule(new OSCDataBinding("/dv/autosave/time", &autoSaveTime, true, minuteConverter));

    oscDataRouter->addRule(new OSCDataBinding("/dv/stats/runningTime", &runningTime, true, hourConverter));
    oscDataRouter->addRule(new OSCDataBinding("/dv/stats/restartCount", &restartCount, true));

    oscDataRouter->addRule(
            new OSCDataBinding("/dv/timestar/duration/min", &timeStarMinDuration, true, secondConverter));
    oscDataRouter->addRule(
            new OSCDataBinding("/dv/timestar/duration/max", &timeStarMaxDuration, true, secondConverter));
    oscDataRouter->addRule(new OSCDataBinding("/dv/timestar/randomFactor", &timeStarRandomOnFactor, true));
    oscDataRouter->addRule(new OSCDataBinding("/dv/timestar/brightness/min", &timeStarMinBrightness, true));
    oscDataRouter->addRule(new OSCDataBinding("/dv/timestar/brightness/max", &timeStarMaxBrightness, true));
    defaultBrightness.addToOSCRouter(oscDataRouter, "/dv/led/%i/default", true);

    oscDataRouter->addRule(new OSCDataBinding("/dv/wave/brightness/min", &waveMinBrightness, true));
    oscDataRouter->addRule(new OSCDataBinding("/dv/wave/brightness/max", &waveMaxBrightness, true));
    oscDataRouter->addRule(new OSCDataBinding("/dv/wave/travelSpeed", &waveTravelSpeed, true, deciSecondConverter));
    oscDataRouter->addRule(new OSCDataBinding("/dv/wave/duration", &waveDuration, true, deciSecondConverter));
}

float AppSettings::getMinBrightness() const {
    return minBrightness.get();
}

void AppSettings::setMinBrightness(float minBrightness) {
    AppSettings::minBrightness.set(minBrightness);
}

float AppSettings::getMaxBrightness() const {
    return maxBrightness.get();
}

void AppSettings::setMaxBrightness(float maxBrightness) {
    AppSettings::maxBrightness.set(maxBrightness);
}

unsigned long AppSettings::getTimeStarMinDuration() const {
    return timeStarMinDuration.get();
}

void AppSettings::setTimeStarMinDuration(unsigned long timeStarMinDuration) {
    AppSettings::timeStarMinDuration.set(timeStarMinDuration);
}

unsigned long AppSettings::getTimeStarMaxDuration() const {
    return timeStarMaxDuration.get();
}

void AppSettings::setTimeStarMaxDuration(unsigned long timeStarMaxDuration) {
    AppSettings::timeStarMaxDuration.set(timeStarMaxDuration);
}

float AppSettings::getTimeStarRandomOnFactor() const {
    return timeStarRandomOnFactor.get();
}

void AppSettings::setTimeStarRandomOnFactor(float timeStarRandomOnFactor) {
    AppSettings::timeStarRandomOnFactor.set(timeStarRandomOnFactor);
}

float AppSettings::getTimeStarMinBrightness() const {
    return timeStarMinBrightness.get();
}

void AppSettings::setTimeStarMinBrightness(float timeStarMinBrightness) {
    AppSettings::timeStarMinBrightness.set(timeStarMinBrightness);
}

float AppSettings::getTimeStarMaxBrightness() const {
    return timeStarMaxBrightness.get();
}

void AppSettings::setTimeStarMaxBrightness(float timeStarMaxBrightness) {
    AppSettings::timeStarMaxBrightness.set(timeStarMaxBrightness);
}

int AppSettings::getVersion() const {
    return version.get();
}

bool AppSettings::isGammaCorrection() const {
    return gammaCorrection.get();
}

void AppSettings::setGammaCorrection(bool gammaCorrection) {
    AppSettings::gammaCorrection.set(gammaCorrection);
}

unsigned long AppSettings::getAppFrameRate() const {
    return appFrameRate.get();
}

unsigned long AppSettings::getShowSpeed() const {
    return showSpeed.get();
}

void AppSettings::setShowSpeed(unsigned long showSpeed) {
    AppSettings::showSpeed.set(showSpeed);
}

bool AppSettings::isAutoSave() const {
    return autoSave.get();
}

void AppSettings::setAutoSave(bool autoSave) {
    AppSettings::autoSave.set(autoSave);
}

unsigned long AppSettings::getAutoSaveTime() const {
    return autoSaveTime.get();
}

void AppSettings::setAutoSaveTime(unsigned long autoSaveTime) {
    AppSettings::autoSaveTime.set(autoSaveTime);
}

const bool AppSettings::isSceneControllerOn() const {
    return sceneControllerOn.get();
}

void AppSettings::setSceneControllerOn(bool value) {
    sceneControllerOn.set(value);
}

unsigned long AppSettings::getRunningTime() const {
    return runningTime.get();
}

void AppSettings::setRunningTime(unsigned long value) {
    AppSettings::runningTime.set(value);
}

void AppSettings::incRunningTime(unsigned long value) {
    AppSettings::runningTime.set(runningTime.get() + value);
}

unsigned int AppSettings::getRestartCount() const {
    return restartCount.get();
}

void AppSettings::setRestartCount(unsigned int value) {
    restartCount.set(value);
}

void AppSettings::incRestartCount() {
    restartCount.set(restartCount.get() + 1);
}

const float AppSettings::getDefaultBrightness(int index) const {
    return defaultBrightness.get(index);
}

void AppSettings::setGammaFactor(float value) {
    gammaFactor.set(value);
}

float AppSettings::getGammaFactor() {
    return gammaFactor.get();
}

unsigned long AppSettings::getWaveDuration() const {
    return waveDuration.get();
}

void AppSettings::setWaveDuration(unsigned long value) {
    waveDuration.set(value);
}

unsigned long AppSettings::getWaveTravelSpeed() const {
    return waveTravelSpeed.get();
}

void AppSettings::setWaveTravelSpeed(unsigned long value) {
    waveTravelSpeed.set(value);
}

float AppSettings::getWaveMinBrightness() const {
    return waveMinBrightness.get();
}

void AppSettings::setWaveMinBrightness(float value) {
    waveMinBrightness.set(value);
}

float AppSettings::getWaveMaxBrightness() const {
    return waveMaxBrightness.get();
}

void AppSettings::setWaveMaxBrightness(float value) {
    waveMaxBrightness.set(value);
}
