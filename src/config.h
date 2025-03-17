#pragma once



//Buttons
#define NAVIGATE_UP D6
#define NAVIGATE_DOWN D7
#define NAVIGATE_ENTER D1

#define KEYSWITCH D2
#define CLEANING_BUTTON D5


//OLED
#define OLED_ADDRESS 0x3C

// PUMPS
#define PUMP_COUNT 4

#define PUMP0_INGREDIENT "Vodka"
#define PUMP0_PIN A0
#define PUMP0_RATE 100

#define PUMP1_INGREDIENT "Tequila"
#define PUMP1_PIN D8
#define PUMP1_RATE 200

#define PUMP2_INGREDIENT "Saft"
#define PUMP2_PIN D0
#define PUMP2_RATE 300

#define PUMP3_INGREDIENT "Grenadine"
#define PUMP3_PIN D4
#define PUMP3_RATE 400

#define DEBOUNCE_TIME 300