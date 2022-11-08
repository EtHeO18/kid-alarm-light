#include "Time.h"

WiFiUDP ntpUdpClient;

NTPClient timeClient(ntpUdpClient, "europe.pool.ntp.org", 3600, 60000);

TimeChangeRule CEST = {"CEST", Last, Sun, Mar, 2, 60};     //Central European Time (Frankfurt, Paris)
TimeChangeRule CET = {"CET ", Last, Sun, Oct, 3, 0};      //Central European Time (Frankfurt, Paris)
Timezone CE(CEST, CET);


void Time_loop(){
  
//  Serial.println(timeClient.getFormattedTime());
  timeClient.update();

}


time_t syncProvider(){
  
  Serial.println("Getting a new time");
  Time_loop();
  
  time_t utc = timeClient.getEpochTime();
  time_t local = CE.toLocal(utc);
//  Serial.printf("utc: %d, local: %d\n", utc, local);

  return local;
}

void Time_setup(){
  
  timeClient.begin();
  timeClient.forceUpdate();

  //MQTT_publish("wordclock", String(timeClient.getEpochTime()));
  setTime(timeClient.getEpochTime());
  
  setSyncProvider(syncProvider);
  //Set Sync Intervals
  setSyncInterval(300);

  Time_loop();
}

