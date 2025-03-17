#include "Recipes.h"
#include "Arduino.h"
#define MAX_INGREDIENTS 4

const char *sunrise_p1_ingredients[MAX_INGREDIENTS] = {"Tequila", "Vodka", {}, {}};
long sunrise_p1_amounts[MAX_INGREDIENTS] = {20, 10, 0, 0};
const char *sunrise_p2_ingredients[MAX_INGREDIENTS] = {"Grenadine", {}, {}, {}};
long sunrise_p2_amounts[MAX_INGREDIENTS] = {15, 0, 0, 0};

const char *test2_p1_ingredients[MAX_INGREDIENTS] = {"Tequila", "Vodka", {}, {}};
long test2_p1_amounts[MAX_INGREDIENTS] = {20, 10, 0, 0};
const char *test2_p2_ingredients[MAX_INGREDIENTS] = {"Grenadine", {}, {}, {}};
long test2_p2_amounts[MAX_INGREDIENTS] = {15, 0, 0, 0};


void Recipes::init(){
    this->recipes[0] = Recipe("Sunrise", sunrise_p1_ingredients, sunrise_p1_amounts, sunrise_p2_ingredients, sunrise_p2_amounts);
    this->recipes[1] = Recipe("test2", test2_p1_ingredients, test2_p1_amounts, test2_p2_ingredients, test2_p2_amounts);
}

void Recipes::getAllNames(const char **buff)
{
    for (int x = 0; x < RECIPE_COUNT; x++)
    {
        buff[x] = this->recipes[x].getName();
        Serial.print("..");
        Serial.println(this->recipes[x].getName());
    }
}

void Recipes::execute(const char *name)
{
    for (int x = 0; x < RECIPE_COUNT; x++)
    {
        if (!strcmp(name, this->recipes[x].getName()))
        {
            this->recipes[x].execute();
            return;
        }
    }
    Serial.print("Error recipe not found: ");
    Serial.println(name);
}