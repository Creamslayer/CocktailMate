#ifndef UNIT_TEST

#include <Arduino.h>
#include <Wire.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>

#include "states.h"
#include "Pumps.h"
#include "Recipes.h"
#include "Navigation.h"

States state = ENTER_LOCK;

SSD1306AsciiWire oled;

int enter_idle();
int idle();
int enter_lock();
int lock();
int enter_cleaning();
int cleaning();
int enter_cocktail();
int cocktail();

Recipes recipes;
Pumps pumps;
Navigation navigation;

const char *currentRecipe;

void setup()
{

  Serial.begin(74880);

  recipes.init();
  navigation.init(&recipes);

  Wire.begin();
  Wire.setClock(100000);

  delay(1000);

  oled.begin(&Adafruit128x64, OLED_ADDRESS);
  oled.setFont(System5x7);
  oled.clear();
  oled.set1X();
  oled.println(F("Cocktail Bar v1.1"));
  oled.println(F("Ready!"));
  Serial.println("Starting in 1 seconds.");
  delay(1000);
}

void loop()
{
  delay(50);

  switch (state)
  {
  case ENTER_IDLE:
    enter_idle();
    break;
  case IDLE:
    idle();
    break;
  case ENTER_LOCK:
    enter_lock();
    break;
  case LOCK:
    lock();
    break;
  case ENTER_CLEANING:
    enter_cleaning();
    break;
  case CLEANING:
    cleaning();
    break;
  case COCKTAIL:
    cocktail();
    break;
  default:
    break;
  }
}

int enter_lock()
{
  Serial.println("Enter Lock");

  oled.clear();
  oled.setCursor(0, 0);
  oled.println(F("System locked"));
  oled.println(F("Turn key to start"));

  state = LOCK;
  return 0;
}

int lock()
{
  Serial.println("Lock");

  if (!navigation.lock())
    state = ENTER_IDLE;

  delay(300);
  return 0;
}

int enter_idle()
{
  Serial.println("Enter Idle Select Cocktail");

  oled.clear();
  oled.setCursor(0, 0);
  oled.println(F("Select cocktail:\n"));

  navigation.updateDisplay(currentRecipe);
  oled.println(currentRecipe);
  Serial.println(currentRecipe);

  state = IDLE;
  return 0;
}

int idle()
{

  if (navigation.updateDisplay(currentRecipe))
  {
    oled.setCursor(0, 2);
    oled.print("                   ");
    oled.setCursor(0, 2),
        oled.println(currentRecipe);
    Serial.println(currentRecipe);
  }

  if (navigation.enterCleaning())
  {
    state = ENTER_CLEANING;
    return 0;
  }

  if (navigation.executeRecipe())
  {
    state = COCKTAIL;
  }

  if (navigation.lock())
  {
    state = ENTER_LOCK;
  }

  return 0;
}

int enter_cleaning()
{
  Serial.println("\nEnter Cleaning");

  oled.clear();
  oled.setCursor(0, 0);
  oled.println(F("Cleaning........"));
  oled.println();

  state = CLEANING;
  return 0;
}

int cleaning()
{
  Serial.println("\nCleaning.......");

  for (int x = 0; x < 15; x++)
  {
    oled.print(".");
    Serial.print(".");
    pumps.clean(1000);
  }
  Serial.println();

  state = ENTER_IDLE;
  return 0;
}

int cocktail()
{
  Serial.println("Enter Cocktail");
  Serial.println(currentRecipe);

  oled.clear();
  oled.setCursor(0, 0);
  oled.println("Recipe:");
  oled.println(currentRecipe);

  recipes.execute(currentRecipe);
  state = ENTER_IDLE;
  return 0;
}

#endif