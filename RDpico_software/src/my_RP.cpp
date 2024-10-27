// =========================================================================================================================================
//                                                 Rotating Display RD56m
//                                                    © Ludwin Monz
// License: Creative Commons Attribution - Non-Commercial - Share Alike (CC BY-NC-SA)
// you may use, adapt, share. If you share, "share alike".
// you may not use this software for commercial purposes 
// =========================================================================================================================================

#include "my_RP.h"
#include "FlashFS.h"

#include <Arduino.h>
#include "pico/cyw43_arch.h"
#include <WiFi.h>
#include <time.h>

#define TIME_ZONE "CET-1CEST,M3.5.0/02,M10.5.0/03" // https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv    
                                                   // this is only the default (my home ;-)       
#define myNTP1 "pool.ntp.org"
#define myNTP2 "time.nist.gov"

// =========================================================================================================================================
//                                                      Constructor
// =========================================================================================================================================

my_RP::my_RP() {
}

// =========================================================================================================================================
//                                                      begin Method
// =========================================================================================================================================

void my_RP::begin() {

  // initiate SD card
  _dummy.begin();                   // calls FlashFS for the first time

  FlashFS _test{"/variables/"};
  Serial.println(_test.listFilesInJson());

  // initiate Wifi
  _iniWifi();

  // set time
  initMyTime();
}

// =========================================================================================================================================
//                                                      Wifi Methods
// =========================================================================================================================================

void my_RP::_iniWifi() {
  /*
    read SSID and password, if available
  */
  Serial.println ("start initialization....");

  _ssid = _ssid_f.read_f();
  _password = _password_f.read_f();

  Serial.println(_ssid);
  Serial.println(_password);

  /*
    try to connect to WiFi, if ssid and password are valid
  */
  if ((_ssid!="")|(_password!="")) { 
//    WiFi.mode(WIFI_STA);
    WiFi.begin(_ssid.c_str(), _password.c_str());

    Serial.print("connecting to WiFi ...");

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 10) {
      delay(1000);
      Serial.print(".");
      attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
      ssid = _ssid;
      ipAddress = WiFi.localIP().toString();
      Serial.println("WiFi connected: "+ipAddress);
  } else {
      Serial.println("Wifi connection failed...");
    }
  }

  if (WiFi.status() != WL_CONNECTED) {
//    WiFi.mode(WIFI_AP);
    IPAddress apIP(192, 168, 4, 1);         //
    IPAddress subnet(255,255,255,0);        //
    WiFi.softAPConfig(apIP, apIP, subnet);  //

    ssid = "RD56m";
    WiFi.softAP(_ssid.c_str());             //

    ipAddress = WiFi.softAPIP().toString();

    Serial.println("Access Point started.");
    Serial.print("IP-Adresse: ");
    Serial.println(ipAddress);  
  }

}

// =========================================================================================================================================
//                                                      Time Methods
// helpful tutorial: https://randomnerdtutorials.com/esp32-ntp-timezones-daylight-saving/
// =========================================================================================================================================

void my_RP::initMyTime() {

  configTime(0, 0, myNTP1, myNTP2);    // First connect to NTP server, with 0 TZ offset

  _timeZone = _timeZone_f.read_f();
  if (_timeZone == "") _timeZone = TIME_ZONE;

  setenv("TZ",_timeZone.c_str(),1);  //  Now adjust the TZ
  tzset();
}

void my_RP::getMyTime() {
  tm local;
  time_t now;                       // this is a time stamp
  now = time(NULL);                 // read the current time stamp
  local = *localtime(&now);         // update the structure "local" with the current time

  Hour = local.tm_hour;
  Min = local.tm_min;
  Sec = local.tm_sec;
  Mday = local.tm_mday;
  Mon = local.tm_mon + 1;
  Year = local.tm_year + 1900;
  Wday = local.tm_wday;

  tm1 = local;
}

