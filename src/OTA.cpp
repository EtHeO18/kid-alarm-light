#include "OTA.h"

const char* OTApass = "konijntje-OTA";

void OTA_setup(){

    ArduinoOTA.setPassword(OTApass);

    ArduinoOTA.onStart([]() {
      Serial.println("OTA Start");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("OTA Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onEnd([]() {
      Serial.println("OTA End");
    });

    ArduinoOTA.onError([](ota_error_t error) {
      
      Serial.printf("OTA Error[%u]: ", error);
      
      switch(error){
        case OTA_AUTH_ERROR:
          Serial.println("Auth Failed");
          break;

        case OTA_BEGIN_ERROR:
          Serial.println("Begin Failed");
          break;

        case OTA_CONNECT_ERROR:
          Serial.println("Connect Failed");
          break;

        case OTA_RECEIVE_ERROR:
          Serial.println("Receive Failed");
          break;

        case OTA_END_ERROR:
          Serial.println("End Failed");
          break;
      }
      
      ESP.restart();
    });
    
    ArduinoOTA.begin();

}

void OTA_loop(){
  #if DEBUG_GENERAL
  Serial.println("OTA_loop()");
  #endif
  ArduinoOTA.handle();
}
