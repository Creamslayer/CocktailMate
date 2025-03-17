#include <Arduino.h>

#include "Navigation.h"


const char* test = "test";

void Navigation::init(Recipes *recipes)
{
    pinMode(NAVIGATE_UP, INPUT_PULLUP);
    pinMode(NAVIGATE_DOWN, INPUT_PULLUP);
    pinMode(NAVIGATE_ENTER, INPUT_PULLUP);
    pinMode(KEYSWITCH, INPUT_PULLUP);
    pinMode(CLEANING_BUTTON, INPUT_PULLUP);

    recipes->getAllNames(this->allCocktails);

    currentCocktail = 0;
    lastPress = 0;
}

bool Navigation::updateDisplay(const char *&buff)
{
    buff = allCocktails[currentCocktail];



    if (millis() < lastPress + DEBOUNCE_TIME)
        return false;

    if (!digitalRead(NAVIGATE_UP))
    {
        lastPress = millis();
        currentCocktail = (currentCocktail + RECIPE_COUNT + 1) % RECIPE_COUNT;
        buff = allCocktails[currentCocktail];
        return true;
    }

    if (!digitalRead(NAVIGATE_DOWN))
    {
        lastPress = millis();
        currentCocktail = (currentCocktail + RECIPE_COUNT - 1) % RECIPE_COUNT;
        buff = allCocktails[currentCocktail];
        return true;
    }

    

    
    return false;
}

bool Navigation::lock()
{
    return !digitalRead(KEYSWITCH);
}

bool Navigation::executeRecipe()
{
    if (millis() < lastPress + DEBOUNCE_TIME)
        return false;

    if (!digitalRead(NAVIGATE_ENTER))
    {
        lastPress = millis();
        return true;
    }

    return false;
}

bool Navigation::enterCleaning()
{
    if (millis() < lastPress + DEBOUNCE_TIME)
        return false;

    if (!digitalRead(CLEANING_BUTTON))
    {
        lastPress = millis();
        return true;
    }

    return false;
}