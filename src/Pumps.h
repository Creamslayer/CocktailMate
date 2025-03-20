#pragma once

#include "Pump.h"
#include "config.h"

class Pumps
{

private:
    Pump pumps[PUMP_COUNT] = {
        {PUMP0_INGREDIENT, PUMP0_PIN, PUMP0_RATE},
        {PUMP1_INGREDIENT, PUMP1_PIN, PUMP1_RATE},
        {PUMP2_INGREDIENT, PUMP2_PIN, PUMP2_RATE},
        {PUMP3_INGREDIENT, PUMP3_PIN, PUMP3_RATE}};

public:
    Pumps() {};
    long pump(const char *, long);
    bool update();
    void clean(unsigned long);

private:
    Pump *getPump(const char *);
};