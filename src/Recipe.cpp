#include "Recipe.h"
#include <Arduino.h>
#include "Pumps.h"


extern Pumps pumps;

Recipe::Recipe(const char *name, const char **phase1_ingredients, long *phase1_amounts, const char **phase2_ingredients, long *phase2_amounts) : name(name), phase1_ingredients(phase1_ingredients), phase1_amounts(phase1_amounts), phase2_ingredients(phase2_ingredients), phase2_amounts(phase2_amounts)
{
}

void Recipe::execute()
{
    Serial.print("=======  Executing recipe: ");
    Serial.print(this->getName());
    Serial.println("=======");

    //Phase1:
    for(int x = 0;x<MAX_INGEDIENTS && phase1_ingredients[x] != NULL;x++){
        pumps.pump(phase1_ingredients[x], phase1_amounts[x]);
    }
    while(pumps.update()){
        delay(50);
    }

    //Phase2
    for(int x = 0;x<MAX_INGEDIENTS && phase2_ingredients[x] != NULL;x++){
        pumps.pump(phase2_ingredients[x], phase2_amounts[x]);
    }
    while(pumps.update()){
        delay(50);
    }

    Serial.println("=======FINISHED=====");

}

const char* Recipe::getName(){
    return this->name;
}