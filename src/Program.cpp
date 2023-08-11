
#include <ArduinoJson.h>
#include <Preferences.h>

#include "Program.hpp"
#include <Arduino.h>

#include "FS.h"


Program::Program(){

}

ProgramEntry* Program::currentEntry(uint8_t weekday, uint8_t hour, uint8_t minute, uint8_t second){

  if(program.size() == 0){
    return NULL;
  }

  ProgramEntry current(weekday, hour, minute, second, 0, 0, 0);

  ProgramEntry* valid = program[program.size() - 1];
  
  // Serial.print("currentEntry() current:    ");
  // current.print();
  // Serial.println();

  for (int i = 0; i < program.size(); i++) {
    // Serial.print("currentEntry() considering ");
    // program[i]->print();

    if(*program[i] <= current){
      // Serial.println(" is not valid");
      break;
    }else{
      valid = program[i];
      // Serial.println(" is valid");
    }
  }

  if(valid){
    // Serial.print("currentEntry() Have result: ");
    // valid->print();
  }

  return valid;
}

void Program::addNewEntry(uint8_t weekday, uint8_t hour, uint8_t minute, uint8_t second, uint8_t R, uint8_t G, uint8_t B){
  ProgramEntry * entry = new ProgramEntry(weekday, hour, minute, second, R, G, B);
  program.push_back(entry);
}



void Program::load(){
  for(int a=1; a<=7; a++){
    addNewEntry(a, 8, 30, 0, 0x00, 0xFF, 0x00);
    addNewEntry(a, 21, 00, 0, 0xFF, 0x00, 0x00);
  }
  Serial.println("Loaded default program");
  
}

void Program::save(){
  Serial.println("Saving program");
  #if defined(ARDUINOJSON_VERSION_MAJOR) && ARDUINOJSON_VERSION_MAJOR >= 6
      DynamicJsonDocument json(1024);
  #else
      DynamicJsonBuffer jsonBuffer;
      JsonObject& json = jsonBuffer.createObject();
  #endif

      auto entries = json.to<JsonArray>();

      for (int i = 0; i < program.size(); i++) {
        auto obj = entries.createNestedObject();
        obj["weekday"] = program[i]->weekday;
        obj["hour"] = program[i]->hour;
        obj["minute"] = program[i]->minute;
        obj["second"] = program[i]->second;
      }
  
      json["entries"] = entries;
  
      File configFile = SPIFFS.open("/program.json", "w");
      if (!configFile) {
        Serial.println("failed to open program file for writing");
      }
  
  #if defined(ARDUINOJSON_VERSION_MAJOR) && ARDUINOJSON_VERSION_MAJOR >= 6
      serializeJson(json, Serial);
      serializeJson(json, configFile);
  #else
      json.printTo(Serial);
      json.printTo(configFile);
  #endif
    configFile.close();
    //end save
}
