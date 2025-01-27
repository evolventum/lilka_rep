#pragma once

#include "service.h"

class TemperatureSensor : public Service {
public:
    TemperatureSensor();
    int temp_now();
private:
    void run() override;
};
