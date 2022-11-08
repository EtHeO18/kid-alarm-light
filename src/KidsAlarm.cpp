#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

#include <SoftwareSerial.h>


#include "Wifi.h"
#include "Led.h"
#include "Time.h"
#include "OTA.h"
#include "MQTT.h"

#include "TaskScheduler.h"

#include "Program.hpp"
Program program;


int prevMinute = -1;

ProgramEntry* current = NULL;

void renderTime(){

  auto currentEntry = program.currentEntry(weekday(), hour(), minute(), second());
  
  if(!currentEntry){
    // Serial.println("!currentEntry");
    return;
  }

  if(currentEntry == current){
    // Serial.println("currentEntry == current");
    return;
  }

  current = currentEntry;

  CRGB target;
  target.r = current->R;
  target.g = current->G;
  target.b = current->B;

  fadeTo(target);

}


Scheduler runner;


void setup() {
 
  new Task(5000 * TASK_MILLISECOND, TASK_FOREVER, &renderTime, &runner, true);
  new Task(1 * TASK_MILLISECOND, TASK_FOREVER, &fadeTask, &runner, true);

  program.load();

  Serial.begin(115200);

  Wifi_setup();
  Led_setup();
  Time_setup();
  MQTT_setup();
  OTA_setup();

}


void loop() {
  Time_loop();
  MQTT_loop();
  OTA_loop();

  runner.execute();

  String command;

  while(Serial.available()) {

    command = Serial.readString();// read the incoming data as string

    Serial.print("Have command: ");
    Serial.println(command);

    int index = command.indexOf(":");
    if(index >= 0){
      String name = command.substring(0, index);
      Serial.print("Have command name: ");
      Serial.println(name);
      if(name.equals("t")){


        //Nov 07 2022 10:12:54
        //t:1667815974

        //Nov 07 2022 20:11:37
        //t:1667848297

        String timestamp = command.substring(index+1);
        int value = timestamp.toInt();
        setTime(value);
        Serial.print("Set timestamp value to: ");
        Serial.println(value);
      }else if(name.equals("c")){
        //c:0xff4000
        //c:0xff0000
        String color = command.substring(index+1);
        if(color.startsWith("0x")){
          color = color.substring(2);
        }

        int value = strtol(color.c_str(), NULL, 16);

        CRGB target;
        target.r = (value >> 16) & 0xFF;
        target.g = (value >>  8) & 0xFF;
        target.b = (value >>  0) & 0xFF;

        fadeTo(target);
      }
    }

  }

}
