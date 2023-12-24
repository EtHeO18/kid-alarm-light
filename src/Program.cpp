
#include <ArduinoJson.h>
#include <Preferences.h>

#include "Program.hpp"
#include <Arduino.h>

#include "FS.h"
#include <LittleFS.h>


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

  for (size_t i = 0; i < program.size(); i++) {
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


void Program::load(String programJson){
  
  DynamicJsonDocument json(1024*10);

  auto error = deserializeJson(json, programJson);
  if(error == error.Ok){
    Serial.println("Read this program:");
    serializeJson(json, Serial);
    Serial.println();
  }else if(error == error.EmptyInput){
    Serial.println("Empty input");
  }else if(error == error.IncompleteInput){
    Serial.println("Incomplete input");
  }else if(error == error.InvalidInput){
    Serial.println("Invalid input");
  }else if(error == error.NoMemory){
    Serial.println("No Memory");
  }else if(error == error.TooDeep){
    Serial.println("Too deep");
  }


  Serial.print("It has ");
  Serial.print(json.size());
  Serial.println(" entries.");

  program.clear();

  for(size_t i = 0; i < json.size(); i++){
    auto jsonEntry = json[i];

    addNewEntry(
      jsonEntry["weekday"],
      jsonEntry["hour"],
      jsonEntry["minute"],
      jsonEntry["second"],
    
      jsonEntry["r"],
      jsonEntry["g"],
      jsonEntry["b"]
    );
    Serial.print("added entry, program size: ");
    Serial.println(program.size());
  }
}

void Program::load(){

  File configFile = LittleFS.open(PROGRAM_CONFIG_PATH, "r");
  if (!configFile) {
    Serial.println("failed to open program file for reading");
    return;
  }

  auto programJson = configFile.readString();

  Serial.println("Read config:");
  Serial.println(programJson);

  this->load(programJson);
  
}

void Program::save(){
  Serial.println("Saving program");
  #if defined(ARDUINOJSON_VERSION_MAJOR) && ARDUINOJSON_VERSION_MAJOR >= 6
      DynamicJsonDocument json(4096);
  #else
      DynamicJsonBuffer jsonBuffer;
      JsonObject& json = jsonBuffer.createObject();
  #endif

      auto entries = json.to<JsonArray>();

      for (size_t i = 0; i < program.size(); i++) {
        auto obj = entries.createNestedObject();
        obj["weekday"] = program[i]->weekday;
        obj["hour"] = program[i]->hour;
        obj["minute"] = program[i]->minute;
        obj["second"] = program[i]->second;
        obj["r"] = program[i]->R;
        obj["g"] = program[i]->G;
        obj["b"] = program[i]->B;
      }
  
      json["entries"] = entries;
  
      File configFile = LittleFS.open(PROGRAM_CONFIG_PATH, "w");
      if (!configFile) {
        Serial.println("failed to open program file for writing");
      }
  
  #if defined(ARDUINOJSON_VERSION_MAJOR) && ARDUINOJSON_VERSION_MAJOR >= 6
      Serial.println("Saving program:");
      serializeJson(json, Serial);
      Serial.println();
      auto written = serializeJson(json, configFile);
      Serial.print("Written ");
      Serial.print(written);
      Serial.println(" bytes");
  #else
      json.printTo(Serial);
      json.printTo(configFile);
  #endif
    configFile.close();
    //end save
}
