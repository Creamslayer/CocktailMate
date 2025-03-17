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

  // oledPH.begin(&Adafruit128x64, //oledPH_ADDRESS);
  // oledPH.setFont(System5x7);
  // oledPH.clear();
  // oledPH.set1X();
  // oledPH.println(F("Cocktail Bar v1.1"));
  // oledPH.println(F("Ready!"));
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

  // oledPH.clear();
  // oledPH.setCursor(0, 0);
  // oledPH.println(F("System locked"));
  // oledPH.println(F("Turn key to start"));

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

  // oledPH.clear();
  // oledPH.setCursor(0, 0);
  // oledPH.println(F("Select cocktail:"));

  navigation.updateDisplay(currentRecipe);
  // oledPH.println(currentRecipe);
  Serial.println(currentRecipe);

  state = IDLE;
  return 0;
}

int idle()
{

  if (navigation.updateDisplay(currentRecipe))
  {
    // oledPH.setCursor(1, 0);
    // oledPH.print("                   ");
    // oledPH.setCursor(1, 0),
    // oledPH.println(currentRecipe);
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

  // oledPH.clear();
  // oledPH.setCursor(0, 0);
  // oledPH.println(F("Cleaning........"));
  // oledPH.println();

  state = CLEANING;
  return 0;
}

int cleaning()
{
  Serial.println("\nCleaning.......");

  for (int x = 0; x < 15; x++)
  {
    delay(1000);
    // oledPH.print(".");
    Serial.print(".");
  }
  Serial.println();

  state = ENTER_IDLE;
  return 0;
}

int cocktail()
{
  Serial.println("Enter Cocktail");
  Serial.println(currentRecipe);

  // oledPH.clear();
  // oledPH.setCursor(0,0);
  // oledPH.println("Recipe:");
  // oledPH.println(currentRecipe);

  recipes.execute(currentRecipe);
  state = ENTER_IDLE;
  return 0;
}


#endif