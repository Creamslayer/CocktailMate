#include "Pump.h"

Pump::Pump(const char *name, int pin, long rate)
{
    this->start_time = 0;
    this->name = name;
    this->pin = pin;
    this->rate = rate;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
};

long Pump::turnOn(long ml)
{
    char buff[100];
    const char *format_string = "Start pumping %s -- %d ml\n";
    sprintf(buff, format_string, this->name, ml);
    Serial.print(buff);

    this->start_time = millis();
    long duration = ml * this->rate;
    this->target_time = start_time + duration;
    digitalWrite(this->pin, HIGH);
    return duration;
}

/**
 * @return true if in progress
 */
bool Pump::checkPump()
{
    if (this->target_time == 0)
        return false;

    long current_time = millis();
    if (this->target_time < current_time)
    {
        char buff[30];
        const char *format_string = "Finished pumping %s\n";
        sprintf(buff, format_string, this->name);
        Serial.print(buff);

        digitalWrite(this->pin, LOW);
        this->target_time = 0;
        return false;
    }
    return true;
}

void Pump::turnOn()
{
    char buff[100];
    const char *format_string = "Start pumping %s\n";
    sprintf(buff, format_string, this->name);
    Serial.print(buff);

    digitalWrite(this->pin, HIGH);
}

void Pump::turnOff()
{

    char buff[30];
    const char *format_string = "Stop pumping %s\n";
    sprintf(buff, format_string, this->name);
    Serial.print(buff);

    digitalWrite(this->pin, LOW);
}

const char *Pump::getName()
{
    return this->name;
}