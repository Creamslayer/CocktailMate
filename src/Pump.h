#pragma once

#include <Arduino.h>
class Pump
{
private:
    const char *name;
    int pin;
    long start_time;
    long target_time;
    long rate;

public:
    Pump(const char *name, int pin, long rate);

    long turnOn(long ms);

    bool checkPump();

    void turnOn();

    void turnOff();

    const char *getName();
};