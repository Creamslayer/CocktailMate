#include "Recipes.h"
#include "Arduino.h"
#define MAX_INGREDIENTS 4

Recipe recipes_arr[RECIPE_COUNT];

const char *const sunrise_name = "Sunrise";
const char *const sunrise_p1_ingredients[MAX_INGREDIENTS] = {"Tequila", "Vodka", nullptr, nullptr};
const long sunrise_p1_amounts[MAX_INGREDIENTS] = {20, 10, 0, 0};
const char *const sunrise_p2_ingredients[MAX_INGREDIENTS] = {"Grenadine", nullptr, nullptr, nullptr};
const long sunrise_p2_amounts[MAX_INGREDIENTS] = {15, 0, 0, 0};

const char *const test2_name = "test2";
const char *const test2_p1_ingredients[MAX_INGREDIENTS] = {"Tequila", "Vodka", nullptr, nullptr};
const long test2_p1_amounts[MAX_INGREDIENTS] = {20, 10, 0, 0};
const char *const test2_p2_ingredients[MAX_INGREDIENTS] = {"Grenadine", nullptr, nullptr, nullptr};
const long test2_p2_amounts[MAX_INGREDIENTS] = {15, 0, 0, 0};

void Recipes::init()
{
    recipes_arr[0] = Recipe(sunrise_name, sunrise_p1_ingredients, sunrise_p1_amounts, sunrise_p2_ingredients, sunrise_p2_amounts);
    recipes_arr[1] = Recipe(test2_name, test2_p1_ingredients, test2_p1_amounts, test2_p2_ingredients, test2_p2_amounts);
}

void Recipes::getAllNames(const char **buff)
{
    for (int x = 0; x < RECIPE_COUNT; x++)
    {
        buff[x] = recipes_arr[x].getName();
        Serial.print("..");
        Serial.println(recipes_arr[x].getName());
    }
}

void Recipes::execute(const char *name)
{
    for (int x = 0; x < RECIPE_COUNT; x++)
    {
        if (!strcmp(name, recipes_arr[x].getName()))
        {
            recipes_arr[x].execute();
            return;
        }
    }
    Serial.print("Error recipe not found: ");
    Serial.println(name);
}