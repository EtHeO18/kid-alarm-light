#include "HTTP.hpp"

#include <ESP8266WebServer.h>

#include "FS.h"
#include <LittleFS.h>


#include <Program.hpp>

ESP8266WebServer server(80);

Program* _program;

int ends_with(const char *str, const char *suffix) {
  size_t str_len = strlen(str);
  size_t suffix_len = strlen(suffix);

  return (str_len >= suffix_len) &&
         (!memcmp(str + str_len - suffix_len, suffix, suffix_len));
}

const char* mimeType(const char* file){
  if(ends_with(file, ".js")){
    return "text/javascript";
  }

  if(ends_with(file, ".css")){
    return "text/css";
  }

  if(ends_with(file, ".html")){
    return "text/html";
  }

  return "text/html";
}

void serveFile(const char* file){
  char buff[256];
  snprintf(buff, sizeof(buff), "/public%s", file);
  auto fh = LittleFS.open(buff, "r");
  if(!fh){
    server.send(404, "text/html", "File not found!");
    return;
  }

  server.send(200, mimeType(buff), fh);
}

void handleRoot() {
  serveFile("/index.html");
}

// void handleSetTime(){
//   if (server.hasArg("plain")== false){ //Check if body received
//     server.send(422, "text/plain", "Body not received");
//     return;
//   }
 
//   String message = "Body received:\n";
//           message += server.arg("plain");
//           message += "\n";

//   server.send(200, "text/plain", message);
//   Serial.println(message);
// }

void handleGetProgram(){
  auto fh = LittleFS.open(PROGRAM_CONFIG_PATH, "r");
  if(!fh){
    server.send(404, "text/html", "File not found!");
    return;
  }
  server.send(200, "application/json", fh.readString());
}

void handleNotFound(){
  serveFile(server.uri().c_str());
}

void handleSaveProgram(){
    if (!server.hasArg("plain")){
      server.send(400, "text/plain", "Program missing");
      return;
    }

    auto json = server.arg("plain");
    _program->load(json);
    _program->save();
    
    server.send(200, "text/plain", "");
}

void HTTP_setup(Program* program){

  _program = program;

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  // server.on("/settime", HTTP_POST, handleSetTime);
  server.on("/program", HTTP_GET, handleGetProgram);
  server.on("/program", HTTP_POST, handleSaveProgram);
  server.begin();
  Serial.println("HTTP server started");
}

void HTTP_loop(){
  server.handleClient();
}
