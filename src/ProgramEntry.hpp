#include <stdint.h> 
#include  <SoftwareSerial.h>

class ProgramEntry {
  public:
    uint8_t weekday;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t R = 0;
    uint8_t G = 0;
    uint8_t B = 0;

  public:

    void print(){
        Serial.printf("%1d %02d:%02d:%02d 0x%02X%02X%02X", weekday, hour, minute, second, R, G, B);
    }

    ProgramEntry(uint8_t weekday, uint8_t hour, uint8_t R, uint8_t G, uint8_t B): ProgramEntry(weekday, hour, 0, R, G, B){}
    
    ProgramEntry(uint8_t weekday, uint8_t hour, uint8_t minute, uint8_t R, uint8_t G, uint8_t B): ProgramEntry(weekday, hour, minute, 0, R, G, B){}

    ProgramEntry(uint8_t weekday, uint8_t hour, uint8_t minute, uint8_t second, uint8_t R, uint8_t G, uint8_t B);

    int compare(ProgramEntry entry);

    bool operator<=(ProgramEntry entry){
      return this->compare(entry) <= 0;
    }
    bool operator<(ProgramEntry entry){
      return this->compare(entry) < 0;
    }
    
    bool operator>=(ProgramEntry entry){
      return this->compare(entry) >= 0;
    }
    
    bool operator>(ProgramEntry entry){
      return this->compare(entry) > 0;
    }
  
};
