#include <CppUTest/TestHarness.h>
#include <stdint.h>

extern "C" {
#include "led_driver.h"
#include "ringbuffer.h"
}

TEST_GROUP(LedDriverTests){

};

IGNORE_TEST(LedDriverTests, ledDriverShouldPulseCorrectValue) {}
