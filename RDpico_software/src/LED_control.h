// =========================================================================================================================================
//                                                 Rotating Display RD56m
//                                                    © Ludwin Monz
// License: Creative Commons Attribution - Non-Commercial - Share Alike (CC BY-NC-SA)
// you may use, adapt, share. If you share, "share alike".
// you may not use this software for commercial purposes 
// =========================================================================================================================================

// ******************************************************************************************************************************************
//
//          This class manages the multiplexing of the LEDs by means of the RP2040 PIO (programmable IO)
//
//          The file "LED_multiplexer.pio" is the assembler PIO program. It was compiled with the online
//          compiler https://wokwi.com/tools/pioasm. The result is LED_multiplexer.pio.h
// 
// ******************************************************************************************************************************************

#ifndef LED_control_H
#define LED_control_H

#include <Arduino.h>
#include "hardware/pwm.h"
// #include "LED_MUX.pio.h"
#include "LED_multiplexer.pio.h"

#define lpt 240					// lines per turn
#define lineOffset 120   // offset

#define Hall 20
#define PWM0_A 21       // only for test purposes

class LED_control {
  private:
    long static _tpt;												                  // time per turn
    long static _LPT;                                         // lines per turn
    unsigned int static _line_period; 							          // time per line
    void static _HallIRQ(uint gpio, uint32_t events);					// HallIRQ Handler
    void _initHallIRQ();                                      // initiate Hall Interrupt
    void static _PixelIRQ();	                        				// HallIRQ Handler
    void _initPixelIRQ();

    int static _line_counter0;       								    // counts the displayed lines. _line_counter0 is 1/2turn ahead of _line_counter1
    int static _line_counter1;        								    //
    int static _line_offset;

    void _initTestOutput();
    void static _setTestOutput(bool status);

    void _initMultiplexer();
    void static _pioIRQ();
    void _startPattern();
    
  public:
    PIO static pio;
    uint offset;
    uint static sm;

    LED_control();                                       // Constructor

    void begin();                                        // init PIO multiplexer
                                                         // setup interrupts for LED control
    uint8_t static line[1681][7];									   // 240 lines, 8 sublines, 7x8=56 bits
    uint8_t static line_past[1681][7];                // line_past holds the data for the interlaced pixels	
    uint32_t static subline[7][4];                     // there are 8 sublines per line.
                                                        // each subline holds the LED data and the LED group address (4 32 bit words)
    uint8_t static sublineCount;

    uint32_t static brightness;

    unsigned int static line_period;
};

#endif
