// =========================================================================================================================================
//                                                 Rotating Display RD56m
//                                                    © Ludwin Monz
// License: Creative Commons Attribution - Non-Commercial - Share Alike (CC BY-NC-SA)
// you may use, adapt, share. If you share, "share alike".
// you may not use this software for commercial purposes 
// =========================================================================================================================================


// ******************************************************************************************************************************************
//
//   This class provides the rotating display object. It consists of the display data (one bit per LED) and of methods for manipulating
//   the data and for updating the displayed image
//
// ******************************************************************************************************************************************


#ifndef RD_56M_H
#define RD_56M_H

#include <Arduino.h>
#include "LED_control.h"

extern LED_control LEDcontrol;

class RD_56m {
  private:
    struct pixel {
        uint8_t R;
        uint8_t G;
        uint8_t B;
    };
  
    pixel _readBmpPix(unsigned char bmp[][165], int x, int y);                          // read pixel values of bitmap
    void _writeBmpPix(unsigned char bmp[][165], int x, int y, const pixel& Pixel);      // write pixel values of bitmap

    void _writeLinePix(int r, int a, const pixel& Pixel);                               // write line values
    bool help=true;
  
  public:

    int brightness;                                               // brightness level in %
  
    RD_56m();                                                      // constructor
    void begin();                                                 // begin function initiates VSPI

    void upload(int _brightness);                                 // uploads display image data and brightness setting to display controller
    void displayBMP(unsigned char bmp[][165]);                     // displays a bitmap
    void startPattern(int angle);

};

#endif