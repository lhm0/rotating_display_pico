// =========================================================================================================================================
//                                                 Rotating Display RD56m
//                                                    © Ludwin Monz
// License: Creative Commons Attribution - Non-Commercial - Share Alike (CC BY-NC-SA)
// you may use, adapt, share. If you share, "share alike".
// you may not use this software for commercial purposes 
// =========================================================================================================================================

#include <Arduino.h>
#include "FlashFS.h"
#include "my_RP.h"
#include "webInterface.h"
#include "my_BMP.h"
#include "LED_control.h"
#include "RD_56m.h"

#include <WiFi.h>
#include <time.h>


// =========================================================================================================================================
// 
//                                                        Rotating Display
//
// The program uses OOP in order to structure data and functions. These are the classes:
//
// 1. my_RP
//    description:    the class manages the resources of the RP pico microcontroller. 
//    key methods:    begin()                                         configures Wifi, i2c interface, sets time 
//                    getMyTime()                                     occupies the time and date attributes (see below) 
//                    myPassword()                                    returns Wifi Password which is being used
//                    mySSID()                                        returns Wifi SSID
//    key attributes: int Sec, int Min, int Hour, ...
//
// 2. RD_56
//    description:    the class provides the rotating display object. It loads the image for display, performs the 
//                    transformation from Cartesian to polar coordinates, and updates the display data field. 
//
//    key methods:    begin()                                         initialize display mode and data transfer to the display controller
//                    upload()                                        uploads display data to the display controller
//                    displayBMP(unsigned char bmp[][14])             displays bitmap
//    key attributes: clockMode, brightness
//
// 3. my_BMP
//    description:    this class generates bitmaps for the display. It provides methods for generating clock and weather screens, 
//                    as well as printing text on bitmaps. The bitmap shall be handed over to the RD56 object. 
//    key methods:    generateBMP(int mode, tm* tm, String* ssid)     generates bitmap according to mode, time, ssid
//    key attributes: bitmap[][]                                      this is a 110x110 pixel bitmap
//
// 4. webInterface
//    description:    the class manages the web user interface. It uses the AsyncWebServer library and runs in the background without any need for
//                    attention. The class provides certain attributes, which are set by the web interface:
//    key methods:    begin(String* ssid_)                            starts AsyncWebServer. ssid is displayed (not changed) in web interface
//    key attributes: int clockMode;                                  mode 0 = IP-address, mode 1 = analog clock, mode 2 = digital clock, mode 3 = logo clock, mode 4 = weather clock
//                    int brightness;                                 brightness value in %
//                    char apiKey[50]="";                             apiKey for openweathermap.org
//                    char location[50]="";                           location for openweathermap.org
//                    char country[20]="";                            country for openweathermap.org
//
//
// =========================================================================================================================================

LED_control LEDcontrol;                                 // instance of the LED_control object

my_RP myRP;                                                  // create instance of my_RP
long lastUpdate=0;                                           // remember the time stamp of last display update
int prevSec=0;

webInterface wi56;                                      // create instance of webInterface

long lastWeather;                                            // remember time of last weather updte
my_BMP myBMP;                                                // create instance of my_BMP


RD_56m RD56m;                                                // create instance of RD_56

int right = 0;


// =========================================================================================================================

void setup(){

  // Serial port for debugging purposes
  Serial.begin(115200);

  delay(1000);

  Serial.println("start ............");

  myRP.begin();                             // initiates Wifi, time
  String myssid = myRP.ssid;                // withdraw SSID
  String myIpAddress = myRP.ipAddress;
  
  
  wi56.begin(myssid);                       // start web server

  myRP.getMyTime();
  Serial.printf("Zeit: %d:%d:%d\n", myRP.Hour, myRP.Min, myRP.Sec);

  RD56m.begin();                             // initiate RD56 object
}

void setup1() {
  LEDcontrol.begin();
}

void loop() {
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
//


  if ( (((millis()-lastWeather)>60000)&&(wi56.clockMode==4)) || wi56.updateWeather) {     // update weather every 60 seconds OR if update requested with update_weather
    lastWeather=millis();
    Serial.println("request weather data.....");
    myBMP.getWeather(wi56.apiKey, wi56.location);
    wi56.updateWI(myBMP.w_icon, myBMP.w_temp, myBMP.w_humi);              // send updated data to webInterface

    wi56.updateWeather=false;
  }

  myRP.getMyTime();
  if (myRP.Sec!=prevSec) {
    prevSec = myRP.Sec;
    Serial.printf("%d:%d:%d   %d.%d.%d\n", myRP.Hour, myRP.Min, myRP.Sec, myRP.Mday, myRP.Mon, myRP.Year );
  }

  long stamp = millis();                                           // current time
  if ((stamp-lastUpdate)>100) {
    lastUpdate = stamp;
    tm* mytm = &myRP.tm1;                                          // myRP holds time
    myBMP.generateBMP(wi56.clockMode, mytm, myRP.ssid.c_str(), myRP.ipAddress.c_str());  // generate bitmap

    unsigned char (*mybitmap)[165] = myBMP.bitmap;                 // pointer at bitmap array
    Serial.print("+");
    RD56m.displayBMP(mybitmap);                                 // update display data according to bitmap
  }

  wi56.update();
}
