//
// Created by Florian Bruggisser on 2019-05-10.
//

#ifndef DEEP_VISION_INSTALLATION_DEEPVISIONCONSTANTS_H
#define DEEP_VISION_INSTALLATION_DEEPVISIONCONSTANTS_H

// global
#define SLICE_COUNT 7

// serial
#define BAUD_RATE 115200

// network
#define DEVICE_NAME "deep-vision-installation"

#define SSID_NAME "deep-vision"
#define SSID_PASSWORD "dviadzhdk"

#define OTA_PASSWORD "dviadzhdk"
#define OTA_PORT 8266

#define OSC_OUT_PORT 9000
#define OSC_IN_PORT 8000

// ligth rendering
#define PWM_PIN_MAPPING {16, 17, 18, 19, 23, 25, 26}
#define PWM_RESOLUTION 13
#define PWM_FREQUENCY 5000

#endif //DEEP_VISION_INSTALLATION_DEEPVISIONCONSTANTS_H
