#include "unity.h"
#include <Arduino.h>
#include "Navigation.h"

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_function_should_doBlahAndBlah(void) {
  // test stuff
  TEST_PASS();
}

void test_display_update(void) {
  // more test stuff
  Recipes recipes;
  recipes.init();

  Navigation navigation;
  navigation.init(&recipes);
  const char* buff;
  TEST_ASSERT_FALSE(navigation.updateDisplay(buff));
  TEST_PASS();
}



/**
  * For Arduino framework
  */
void setup() {
  delay(500);  // Wait for serial to stabilize
  Serial.begin(115200);
  while (Serial.available()) Serial.read();
  Serial.write("\n\n");
  delay(500);  // Extra delay to clear junk output

  UNITY_BEGIN();
  RUN_TEST(test_function_should_doBlahAndBlah);
  RUN_TEST(test_display_update);
  UNITY_END();
}
void loop() {}

