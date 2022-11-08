#include "ProgramEntry.hpp"

ProgramEntry::ProgramEntry(uint8_t weekday, uint8_t hour, uint8_t minute, uint8_t second, uint8_t R, uint8_t G, uint8_t B){
  this->weekday = weekday;
  this->hour = hour;
  this->minute = minute;
  this->second = second;

  this->R = R;
  this->G = G;
  this->B = B;
}

int ProgramEntry::compare(ProgramEntry entry){
      
  int result = entry.weekday - this->weekday;
  
  if(result == 0){
    result =  entry.hour - this->hour;
  }
  
  if(result == 0){
    result =  entry.minute - this->minute;
  }      
  
  if(result == 0){
    result =  entry.second - this->second;
  }
  
  return result;
  
}
