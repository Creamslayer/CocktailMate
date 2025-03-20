#include "Pumps.h"

long Pumps::pump(const char *name, long amount)
{
    Pump *p = getPump(name);

    if (p == NULL)
        return 0;
    return p->turnOn(amount);
}

Pump *Pumps::getPump(const char *name)
{
    for (int x = 0; x < PUMP_COUNT; x++)
    {
        if (!strcmp(name, this->pumps[x].getName()))
        {
            return &this->pumps[x];
        }
    }

    Serial.print("No Pump found for: ");
    Serial.println(name);
    return NULL;
}

bool Pumps::update()
{
    bool ret = false;

    for (int x = 0; x < PUMP_COUNT; x++)
    {
        ret |= this->pumps[x].checkPump();
    }

    return ret;
}

void Pumps::clean(unsigned long time)
{
    unsigned long start_time = millis();

    for (int x = 0; x < PUMP_COUNT; x++)
    {
        this->pumps[x].turnOn();
    }

    while (millis() < start_time + time)
        ;

    for (int x = 0; x < PUMP_COUNT; x++)
    {
        this->pumps[x].turnOff();
    }
}

void Pumps::pump(int idx)
{
    this->pumps[idx].turnOn();
    delay(50);
    this->pumps[idx].turnOff();
}