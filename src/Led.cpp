
#include "Led.h"

CRGB led;

CRGB source;
CRGB target;

#define FADE_PERIOD 3.0f

int fadeStart = 0;

void fadeTo(const CRGB & dest){

  char buffer[80];

  if(led.r == dest.r && led.g == dest.g && led.b == dest.b){
    return;
  }

  snprintf(buffer, sizeof(buffer), "Have a new target: 0x%02X%02X%02X (old color 0x%02X%02X%02X)\n", dest.r, dest.g, dest.b, led.r, led.g, led.b);
  Serial.println(buffer);
  
  //t:1667815974
  source = led;
  target = dest;

  fadeStart = millis();
}


void displayLed(){
  analogWrite(PIN_RED, led.r);
  analogWrite(PIN_GREEN, led.g);
  analogWrite(PIN_BLUE, led.b);
}

void fadeTask(){
  
  if(fadeStart == 0){
    return;
  }
  
  float fadeInMillis = millis() - fadeStart;
  
  float progress = (fadeInMillis / 1000) / FADE_PERIOD;

  fract8 fract = progress * 256;

  if(progress >= 1.0f){
    led = target;
    source = target;
    fadeStart = 0;
  }else{
    led = source.lerp8(target, fract);
    displayLed();
  }
  
}




void Led_setup(){
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);

  analogWriteRange(255);
  

  pinMode(PIN_BUILTIN_LED, OUTPUT);
  digitalWrite(PIN_BUILTIN_LED, HIGH);
}
