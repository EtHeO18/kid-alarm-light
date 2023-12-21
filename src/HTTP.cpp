#include "HTTP.hpp"

#include <ESP8266WebServer.h>

#include "FS.h"
#include <LittleFS.h>


#include <Program.hpp>

ESP8266WebServer server(80);

Program* _program;

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/
void handleRoot() {
  Serial.println("Serving root");
  auto fh = LittleFS.open("public/index.html", "r");
  if(!fh){
    server.send(404, "text/html", "File not found!");
    return;
  }
  server.send(200, "text/html", fh.readString());
}

void handleSetTime(){
      if (server.hasArg("plain")== false){ //Check if body received
            server.send(200, "text/plain", "Body not received");
            return;
      }
 
      String message = "Body received:\n";
             message += server.arg("plain");
             message += "\n";
 
      server.send(200, "text/plain", message);
      Serial.println(message);
}


void handleSaveProgram(){
    if (!server.hasArg("plain")){
      server.send(400, "text/plain", "Program missing");
      return;
    }

    auto json = server.arg("plain");
    _program->load(json);
    
    server.send(200, "text/plain", "");
}

void HTTP_setup(Program* program){

  _program = program;

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);

  server.on("/settime", handleSetTime);
  server.on("/program", HTTP_POST, handleSaveProgram);
  server.begin();
  Serial.println("HTTP server started");
}

void HTTP_loop(){
  server.handleClient();
}
