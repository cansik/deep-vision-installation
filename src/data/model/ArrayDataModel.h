//
// Created by Florian Bruggisser on 2019-05-01.
//

#ifndef DEEP_VISION_INSTALLATION_ARRAYDATAMODEL_H
#define DEEP_VISION_INSTALLATION_ARRAYDATAMODEL_H


#include <cstdint>
#include <data/eeprom/IEEPROMDataModel.h>
#include <data/osc/OSCDataRouter.h>
#include <data/osc/rule/converter/IOSCBindingConverter.h>
#include <data/osc/rule/OSCDataBinding.h>
#include "DataModel.h"

template<typename T>
class ArrayDataModel : public IEEPROMDataModel {

private:
    typedef DataModel<T> *DataModelPtr;
    typedef DataModelPtr *DataModelArray;

    DataModelArray values;
    T defaultValue;
    int size;

public:
    explicit ArrayDataModel(T defaultValue, int size);

    T get(int index) const {
        return values[index]->get();
    }

    DataModelPtr getModel(int index) const {
        return values[index];
    }

    void set(T value, int index) {
        values[index].set(value);
    }

    void reset() override;

    void saveToEEPROM(int address) override;

    void loadFromEEPROM(int address) override;

    int sizeInEEPROM() override;

    int getSize() const;

    void addToOSCRouter(OSCDataRouter *oscDataRouter, const char *addressTemplate, bool publishOnReceive = false,
                        IOSCBindingConverter *converter = nullptr);

};

template<typename T>
ArrayDataModel<T>::ArrayDataModel(T defaultValue, int size) {
    ArrayDataModel::defaultValue = defaultValue;
    ArrayDataModel::size = size;

    // init array
    values = new DataModel<T>[size];

    // init models
    for (auto i = 0; i < size; i++) {
        values[i] = new DataModel<T>(defaultValue);
    }
}

template<typename T>
void ArrayDataModel<T>::reset() {
    for (auto i = 0; i < size; i++) {
        values[i].reset();
    }
}

template<typename T>
void ArrayDataModel<T>::saveToEEPROM(int address) {
    // read stride from first value
    auto stride = values[0].sizeInEEPROM();

    for (auto i = 0; i < size; i++) {
        values[i]->saveToEEPROM(address + (i * stride));
    }
}

template<typename T>
void ArrayDataModel<T>::loadFromEEPROM(int address) {
    // read stride from first value
    auto stride = values[0].sizeInEEPROM();

    for (auto i = 0; i < size; i++) {
        values[i]->loadFromEEPROM(address + (i * stride));
    }
}

template<typename T>
int ArrayDataModel<T>::sizeInEEPROM() {
    return values[0].sizeInEEPROM() * size;
}

template<typename T>
int ArrayDataModel<T>::getSize() const {
    return size;
}

template<typename T>
void ArrayDataModel<T>::addToOSCRouter(OSCDataRouter *oscDataRouter, const char *addressTemplate, bool publishOnReceive,
                                       IOSCBindingConverter *converter) {
    for (auto i = 0; i < size; i++) {
        // todo: change address by replacing a predefined var
        oscDataRouter->addRule(new OSCDataBinding(addressTemplate, values[i], publishOnReceive, converter));
    }
}


#endif //DEEP_VISION_INSTALLATION_ARRAYDATAMODEL_H
