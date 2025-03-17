#pragma once

#include "config.h"
#include "Recipes.h"

class Navigation
{
private:
    int currentCocktail;
    const char *allCocktails[RECIPE_COUNT];
    long unsigned lastPress;


public:
    Navigation(){};

    void init();
    bool updateDisplay(const char *&buff);
    bool lock();
    bool executeRecipe();
    bool enterCleaning();
};