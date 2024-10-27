// =========================================================================================================================================
//                                                 Rotating Display RD56m
//                                                    © Ludwin Monz
// License: Creative Commons Attribution - Non-Commercial - Share Alike (CC BY-NC-SA)
// you may use, adapt, share. If you share, "share alike".
// you may not use this software for commercial purposes 
// =========================================================================================================================================


// ******************************************************************************************************************************************
//
//          This class manages the ressources of the mikrocontroller:
//              * Wifi
//              * I2C Interface
//              * clock
//              * data and file storage
//
// ******************************************************************************************************************************************

#ifndef my_RP_H
#define my_RP_H

#include <Arduino.h>

#include <WiFi.h>
#include "pico/cyw43_arch.h"
#include <time.h>

#include "FlashFS.h"

class my_RP {
  private:
    void _iniWifi();                       // either connects to known Wifi or starts AP

    FlashFS _dummy{"/variables/dummy.txt"};     // this object is used fpr initialization of the SD card, only
    FlashFS _ssid_f{"/variables/ssid.txt"};
    FlashFS _password_f{"/variables/password.txt"};
    FlashFS _timeZone_f{"/variables/timeZone.txt"};

    String _ssid;                          // ssid read from ssid.txt
    String _password;                      // password read from password.txt
    String _timeZone;                      // POSIX for selected time zone

  public:
    my_RP();                               // Constructor

    void begin();                          // initiate Wifi
                                           // configure I2C
                                           // set time

//    AsyncWebServer server{80};             // AsyncWebServer: Server object is public

    String ipAddress;
    String ssid;

    tm tm1;                                // the structure tm holds time information 
    int Sec;   // Sekunden (0-59)
    int Min;   // Minuten (0-59)
    int Hour;  // Stunden (0-23)
    int Mday;  // Tag des Monats (1-31)
    int Mon;   // Monat (0-11)
    int Year;  // Jahr - 1900
    int Wday;  // Tag der Woche (0-6, Sonntag = 0)

    void initMyTime();
    void getMyTime();

};

#endif
