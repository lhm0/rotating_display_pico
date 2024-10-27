// =========================================================================================================================================
//                                                 Rotating Display RD40
//                                                    © Ludwin Monz
// License: Creative Commons Attribution - Non-Commercial - Share Alike (CC BY-NC-SA)
// you may use, adapt, share. If you share, "share alike".
// you may not use this software for commercial purposes 
// =========================================================================================================================================

#include "RD_56m.h"
#include "RD_56mtrafo.h"

#include <Arduino.h>

// =========================================================================================================================================
//                                                      Constructor
// =========================================================================================================================================

RD_56m::RD_56m() {
//  brightness = 50;
}

// =========================================================================================================================================
//                                                      begin()
// =========================================================================================================================================
void RD_56m::begin() {
  startPattern(0);
}


// =========================================================================================================================================
//                                                      upload() method
// =========================================================================================================================================

void RD_56m::upload(int _brightness) {                                                      // formerly send_lines()    
}

// =========================================================================================================================================
//                                                      displayBMP(unsigned char bmp[][14]) method
// =========================================================================================================================================

void RD_56m::displayBMP(unsigned char bmp[][165]) {
  int r,a;
  RD_56m::pixel P1;
  for (r=0; r<56; r++) {
    for (a=0; a<240; a++) { 
        //reduce intensity of inner pixels
        if ((r==0 && a%20!=0) || (r==1 && a%10!=0) || (r==2 && a%6!=0) || (r==3 && a%3!=0) || (r==4 && a%3!=0) || (r>=5 && r<7 && a%2!=0)) {
          P1.R=0;
          P1.G=0;
          P1.B=0;
        } else {
          uint8_t x, y;
          x = trafo_x[r][a];
          y = trafo_y[r][a];

          P1 = _readBmpPix(bmp, x, y);
        }
        _writeLinePix(r, a, P1);
    }
  }
}

// =========================================================================================================================================
//                                                      methods for testing and manipulating bitmap bits
//                                                               bitmaps are managed in color
// =========================================================================================================================================

RD_56m::pixel RD_56m::_readBmpPix(unsigned char bmp[][165], int x, int y) {
  int y_byte, y_start;
  pixel Pixel;
  y_byte=3*y/2;
  y_start=3*y%2;      // if this value is 0, R is in the lower 4 bits of the byte, otherwise it is in the hogher 4 bits
  if (y_start==0) {
    Pixel.R = bmp[x][y_byte] & 0x0F;
    Pixel.G = bmp[x][y_byte]>>4;
    Pixel.B = bmp[x][y_byte+1] & 0x0F;
  }
  else {
    Pixel.R = bmp[x][y_byte]>>4;
    Pixel.G = bmp[x][y_byte+1] & 0x0F;
    Pixel.B = bmp[x][y_byte+1]>>4;
  }
  return Pixel;
}

void RD_56m::_writeBmpPix(unsigned char bmp[][165], int x, int y, const pixel& Pixel){
  int y_byte, y_start;
  y_byte=3*y/2;
  y_start=3*y%2;                                      // if this value is 0, R is in the lower 4 bits of the byte, otherwise it is in the hogher 4 bits
  if (y_start==0) {
    bmp[x][y_byte] = (Pixel.G<<4) | (Pixel.R & 0x0F);
    bmp[x][y_byte+1] &= 0xF0;                           // delete lower 4 bits
    bmp[x][y_byte+1] |= (Pixel.B & 0X0F);               // replace upper 4 bits with B
  }
  else {
    bmp[x][y_byte] &= 0x0F;                             // delete the upper 4 bits
    bmp[x][y_byte] |= (Pixel.R << 4);                   // replace upper 4 bits with R
    bmp[x][y_byte+1] = (Pixel.B << 4) | (Pixel.G & 0x0F);
  }
}
   

// =========================================================================================================================================
//                                                      methods for manipulating line bits (=LEDs)
//                                                      here, color is converted into grey levels
// =========================================================================================================================================

void RD_56m::_writeLinePix(int r, int a, const pixel& Pixel) {
// LED#   00 01 02 03 04 05 06 07 | 08 09 10 11 12 13 14 15 | 16 17 18 19 20 21 22 23 | 24 25 26 27 28 29 30 31 | 32 33 34 35 36 37 38 39 | 40 41 42 43 44 45 46 47 | 48 49 50 51 52 53 54 55
// byte#   0  3  0  3  0  3  0  3 |  0  4  0  4  0  4  0  4 |  1  4  1  4  1  4  1  4 |  1  5  1  5  1  5  1  5 |  2  5  2  5  2  5  2  5 |  2  6  2  6  2  6  2  6 |  3  6  3  6  3  6  3  6
// bit#    0  4  1  5  2  6  3  7 |  4  0  5  1  6  2  7  3 |  0  4  1  5  2  6  3  7 |  4  0  5  1  6  2  7  3 |  0  4  1  5  2  6  3  7 |  4  0  5  1  6  2  7  3 |  0  4  1  5  2  6  3  7
// bank#   0  1  0  1  0  1  0  1 |  0  1  0  1  0  1  0  1 |  0  1  0  1  0  1  0  1 |  0  1  0  1  0  1  0  1 |  0  1  0  1  0  1  0  1 |  0  1  0  1  0  1  0  1 |  0  1  0  1  0  1  0  1


  uint8_t lineByte[56]={0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x01, 0x04, 0x01, 0x04, 0x01, 0x04, 0x01, 0x04, 0x01, 0x05, 0x01, 0x05, 0x01, 0x05, 0x01, 0x05, 0x02, 0x05, 0x02, 0x05, 0x02, 0x05, 0x02, 0x05, 0x02, 0x06, 0x02, 0x06, 0x02, 0x06, 0x02, 0x06, 0x03, 0x06, 0x03, 0x06, 0x03, 0x06, 0x03, 0x06};
  uint8_t lineBit[56] ={0x01, 0x10, 0x02, 0x20, 0x04, 0x40, 0x08, 0x80, 0x10, 0x01, 0x20, 0x02, 0x40, 0x04, 0x80, 0x08, 0x01, 0x10, 0x02, 0x20, 0x04, 0x40, 0x08, 0x80, 0x10, 0x01, 0x20, 0x02, 0x40, 0x04, 0x80, 0x08, 0x01, 0x10, 0x02, 0x20, 0x04, 0x40, 0x08, 0x80, 0x10, 0x01, 0x20, 0x02, 0x40, 0x04, 0x80, 0x08, 0x01, 0x10, 0x02, 0x20, 0x04, 0x40, 0x08, 0x80};

  uint8_t pattern[8][7] = {                                   // parameters are "value" and "bit#"
    {0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 0, 0, 0},
    {1, 1, 1, 1, 1, 0, 0},
    {1, 1, 1, 1, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1}
  };

  uint8_t contrast[71] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 2, 2, 2, 2, 2,  2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  7, 7, 7, 7, 7, 7, 7, 7, 7, 7 , 7};

  a = a*7;
  uint8_t bri = contrast[uint16_t(Pixel.R)*3 + uint16_t(Pixel.G)*6 + uint16_t(Pixel.B)];
  uint8_t byteIndex = lineByte[r];             // which byte to manipulate
  uint8_t bitIndex = lineBit[r];              // which bit within this byte

  for (int as=0; as<7; as++) {

    if (pattern[bri][as]==0) {
        LEDcontrol.line[a+as][byteIndex] &= ~bitIndex;   // clear bit
    } else {
        LEDcontrol.line[a+as][byteIndex] |= bitIndex;    // set bit
    }
  }
} 

void RD_56m::startPattern(int angle) {
	int ln, sl, b;
	for (ln=0; ln<240; ln++) {

    for (sl=0; sl<7; sl++) {
      for (b=0; b<7; b++) LEDcontrol.line[ln*7+sl][b]=0;
    }

    if ((ln>=80)&&(ln<160)) {
      for (b=0; b<7; b++) LEDcontrol.line[ln*7+2][b]=0xFF;
      for (b=0; b<7; b++) LEDcontrol.line[ln*7+4][b]=0xFF;
    }

    if (ln>=160) {
      for (sl=0; sl<7; sl++) for (b=0; b<7; b++) LEDcontrol.line[ln*7+sl][b]=0xFF;
    }
	}
}