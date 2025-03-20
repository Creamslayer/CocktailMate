#pragma once
#define MAX_INGREDIENTS 4
class Recipe
{
private:
    const char *name;
    const char *const *phase1_ingredients;
    const long *phase1_amounts;

    const char *const *phase2_ingredients;
    const long *phase2_amounts;

public:
    Recipe() {};
    Recipe(const char *name, const char *const *phase1_ingredients, const long *phase1_amounts, const char *const *phase2_ingredients, const long *phase2_amounts);
    void execute();
    const char *getName();
};