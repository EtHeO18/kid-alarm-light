#include <FastLED.h>


#define PIN_BUILTIN_LED 2


#define PIN_RED 15
#define PIN_GREEN 12
#define PIN_BLUE 13

#define FADE_PERIOD 3.0f

void Led_setup();
void Led_loop();



void fadeTo(const CRGB & dest);
void fadeTask();