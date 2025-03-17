#pragma once
#define MAX_INGEDIENTS 4
class Recipe
{
private:
    const char *name;
    const char **phase1_ingredients;
    long *phase1_amounts;

    const char **phase2_ingredients;
    long *phase2_amounts;

public:
    Recipe() {};
    Recipe(const char *name, const char **phase1_ingredients, long *phase1_amounts, const char **phase2_ingredients, long *phase2_amounts);
    void execute();
    const char* getName();
};