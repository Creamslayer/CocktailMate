#pragma once
#include "Recipe.h"

#define RECIPE_COUNT 2

class Recipes
{
private:
public:
    Recipes() {};

    void init();
    void execute(const char *);
    void getAllNames(const char **buff);
};