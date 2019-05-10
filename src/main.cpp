#include <Arduino.h>
#include <Wire.h>
#include <ESPmDNS.h>
#include <inttypes.h>
#include <controller/scene/interaction/DefaultScene.h>
#include <controller/scene/InstallationSceneController.h>
#include <controller/scene/show/ShowScene.h>
#include <data/model/DataModel.h>
#include <data/eeprom/EEPROMStorage.h>
#include <data/osc/OSCDataRouter.h>
#include <data/osc/rule/OSCInputAction.h>
#include <data/osc/rule/OSCOutputAction.h>

#include "controller/BaseController.h"
#include "model/Slice.h"
#include "controller/app/Installation.h"
#include "controller/network/NetworkController.h"
#include "controller/network/OTAController.h"
#include "controller/network/OscController.h"
#include "controller/renderer/LightRenderer.h"
#include "controller/scene/BaseScene.h"
#include "controller/scene/SceneController.h"
#include "controller/renderer/SerialLightRenderer.h"
#include "controller/renderer/PWMLightRenderer.h"
#include "controller/scene/star/TimeStarScene.h"
#include "util/MathUtils.h"
#include "DeepVisionConstants.h"

// typedefs
typedef BaseController *BaseControllerPtr;
typedef Slice *SlicePtr;

// controllers
auto network = NetworkController(DEVICE_NAME, SSID_NAME, SSID_PASSWORD, WIFI_STA);
auto ota = OTAController(DEVICE_NAME, OTA_PASSWORD, OTA_PORT);
auto osc = OscController(OSC_IN_PORT, OSC_OUT_PORT);

// data
auto oscRouter = OSCDataRouter(&osc);

// variables
SlicePtr slices[SLICE_COUNT];
auto installation = Installation(SLICE_COUNT, slices, &oscRouter);

// renderer
uint8_t pwmPins[] = PWM_PIN_MAPPING;
LightRenderer *renderer = new PWMLightRenderer(PWM_RESOLUTION, PWM_FREQUENCY, pwmPins, &installation);
LightRenderer *debugRenderer = new SerialLightRenderer(&installation);

// scenes
auto defaultScene = DefaultScene(&installation);
auto showScene = ShowScene(&installation);
auto sceneController = InstallationSceneController(&installation, &defaultScene, &showScene);

// controller list
BaseControllerPtr controllers[] = {
        &network,
        &ota,
        &osc,
        debugRenderer,
        renderer,
        &sceneController,
        &installation
};

// methods
void handleOsc(OSCMessage &msg);

void sendRefresh();

void setupOSCActions();

void setup() {
    Serial.begin(BAUD_RATE);

    // wait some seconds for debugging
    delay(5000);

    // setup random seed
    randomSeed(static_cast<unsigned long>(analogRead(0)));

    // setup slices
    installation.initSlices();

    // load settings
    installation.loadFromEEPROM();
    installation.loadStats();

    // setup controllers
    for (auto &controller : controllers) {
        controller->setup();
    }

    // setup handlers
    osc.onMessageReceived(handleOsc);

    // add osc mdns
    MDNS.addService("_osc", "_udp", OSC_IN_PORT);

    setupOSCActions();

    Serial.printf("setup finished (V: %d)\n", installation.getSettings()->getVersion());
    Serial.printf("OSC Rule Count: %d\n", oscRouter.getRules().size());
    sendRefresh();
}

void loop() {
    // loop controllers
    for (auto &controller : controllers) {
        controller->loop();
    }
}

void setupOSCActions() {
    oscRouter.addRule(new OSCInputAction("/dv/refresh", [](IOSCPublisher *publisher, OSCMessage &msg) {
        sendRefresh();
    }));

    oscRouter.addRule(new OSCInputAction("/dv/show/start", [](IOSCPublisher *publisher, OSCMessage &msg) {
        // todo: implement start
        sendRefresh();
    }));

    oscRouter.addRule(new OSCInputAction("/dv/stats/reset", [](IOSCPublisher *publisher, OSCMessage &msg) {
        installation.resetStats();
        sendRefresh();
    }));

    // brightness control
    auto updateLights = [](IOSCPublisher *publisher, OSCMessage &msg) {
        installation.turnOn();
    };

    oscRouter.addRule(new OSCInputAction("/dv/slice/brightness", updateLights));

    oscRouter.addRule(new OSCInputAction("/dv/installation/on", [](IOSCPublisher *publisher, OSCMessage &msg) {
        installation.getSettings()->setSceneControllerOn(false);
        installation.turnOn();
        sendRefresh();
    }));

    oscRouter.addRule(new OSCInputAction("/dv/installation/off", [](IOSCPublisher *publisher, OSCMessage &msg) {
        installation.getSettings()->setSceneControllerOn(false);
        installation.turnOff();
        sendRefresh();
    }));

    oscRouter.addRule(new OSCInputAction("/dv/settings/load", [](IOSCPublisher *publisher, OSCMessage &msg) {
        installation.loadFromEEPROM();
        osc.send("/dv/status", "Status: loaded");
        sendRefresh();
    }));

    oscRouter.addRule(new OSCInputAction("/dv/settings/save", [](IOSCPublisher *publisher, OSCMessage &msg) {
        installation.saveToEEPROM();
        installation.saveStats();

        osc.send("/dv/status", "Status: saved");
        sendRefresh();
    }));

    oscRouter.addRule(new OSCInputAction("/dv/settings/default", [](IOSCPublisher *publisher, OSCMessage &msg) {
        installation.loadDefaultSettings();

        // send back update info
        osc.send("/dv/status", "Status: default");
        sendRefresh();
    }));
}

void handleOsc(OSCMessage &msg) {
    oscRouter.onReceive(msg);
}

void sendRefresh() {
    oscRouter.publishAll();
}