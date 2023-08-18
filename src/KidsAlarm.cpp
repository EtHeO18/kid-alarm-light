#include "Led.h"
#include "Time.hpp"

#include <Arduino.h>

#include "Program.hpp"

#define _TASK_SLEEP_ON_IDLE_RUN  // Enable 1 ms SLEEP_IDLE powerdowns between runs if no callback methods were invoked during the pass
#define _TASK_STATUS_REQUEST     // Compile with support for StatusRequest functionality - triggering tasks on status change events in addition to time only

#include <TaskScheduler.h>

#include "MQTT.h"
#include "Wifi.h"
#include "HTTP.hpp"



Program program;

int prevMinute = -1;

ProgramEntry* current = NULL;

void renderTime(){

  auto currentEntry = program.currentEntry(weekday(), hour(), minute(), second());
  
  if(!currentEntry){
    Serial.println("!currentEntry");
    return;
  }

  if(currentEntry == current){
    Serial.println("currentEntry == current");
    return;
  }

  Serial.println("Have new relevant entry");

  current = currentEntry;

  CRGB target;
  target.r = current->R;
  target.g = current->G;
  target.b = current->B;

  fadeTo(target);

}

void feedWatchdog(){
  ESP.wdtFeed();
}


Scheduler runner;

Task taskTime(5000, TASK_FOREVER, &renderTime);
Task taskFade(1, TASK_FOREVER, &fadeTask);
// Task taskFeedWatchdog(1000, TASK_FOREVER, &feedWatchdog);


void setup() {
 

  Serial.begin(115200);


  program.load();
  

  runner.init();
  Serial.println("Initialized scheduler");

  runner.addTask(taskTime);
  runner.addTask(taskFade);
  // runner.addTask(taskFeedWatchdog);

  taskTime.enable();
  taskFade.enable();
  // taskFeedWatchdog.enable();

  Serial.println("Scheduled tasks");


  Led_setup();

  jumpTo(CRGB(0xFF00FF));

  Wifi_setup();

  jumpTo(CRGB(0x00FFFF));
  Time_setup();

  jumpTo(CRGB(0x000000));
  // MQTT_setup();
  // OTA_setup();
  // HTTP_setup();

  ESP.wdtEnable(10000);
}


void loop() {
  Time_loop();
  // MQTT_loop();
  // OTA_loop();
  // HTTP_loop();

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
