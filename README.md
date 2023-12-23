# Kid alarm light

## Intro

This is a project to replace my current (broken) [sleeping trainer](https://www.bol.com/nl/nl/p/sleepyy-slaaptrainer-voor-kinderen-kinderwekker-met-nachtlamp-en-wekker-wit-konijn/9300000088630304/).

## Features

- [x] Drive an RGB led based on a schedule
- [x] Get the time from a Wifi connection
- [x] Fluent color easing
- [x] LDR support to adjust the brightness to ambient lighting
- [ ] Put debug statements behind a flag
- [ ] Remote syslog support?
- [ ] Publish MQTT events
- [x] Have the schedule be persistent
- [x] Use LittleFS instead of SPIFFS
- [ ] Web interface to edit the schedule
- [ ] MQTT interface to edit the schedule
- [ ] Adjustable timezone (currently hardcoded in src/Time.cpp)
- [ ] Daylight saving time easing


## Requirements

The project is built for an [esp8266-based board](https://nl.aliexpress.com/item/1005002879902462.html). Any esp8266-based board should do, as long as it has access to an RGB led. For different boards, you'll probably want to change src/Led.h (pinouts) and src/Led.cpp (displayLed function).

## Building

This is built in PlatformIO on VS Code. I have little experience with this, but to my understanding you should just be able to build it.

The frontend part is build with vite, with node v18.17.0. Check the README.md from /vue. After building, be sure to use the "Upload Filesystem Image" from PlatformIO.
