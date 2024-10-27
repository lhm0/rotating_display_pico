// =========================================================================================================================================
//                                                 Rotating Display RD56m
//                                                    © Ludwin Monz
// License: Creative Commons Attribution - Non-Commercial - Share Alike (CC BY-NC-SA)
// you may use, adapt, share. If you share, "share alike".
// you may not use this software for commercial purposes 
// =========================================================================================================================================

#include "LED_control.h"
#include <Arduino.h>


// Definition of static variables
long LED_control::_tpt = 0;
long LED_control::_LPT = lpt;
unsigned int LED_control::_line_period = 30000;
int LED_control::_line_counter0 = 120;
int LED_control::_line_counter1 = 0;
int LED_control::_line_offset = lineOffset;

PIO LED_control::pio = pio0;
uint LED_control::sm = 0;

uint8_t LED_control::line[1681][7];			        // 240 lines, 7 sublines, 7x8=56 bits
uint8_t LED_control::line_past[1681][7];             // line_past holds the data for the interlaced pixels	
uint32_t LED_control::subline[7][4];                        // subline data to be pushed to the LEDs

uint32_t LED_control::brightness = 1;

uint8_t LED_control::sublineCount=0;

unsigned int LED_control ::line_period;

// =========================================================================================================================================
//                                                      Constructor
// =========================================================================================================================================

LED_control::LED_control() {
}

// =========================================================================================================================================
//                                                      begin Method
// =========================================================================================================================================

void LED_control::begin() {
    _initMultiplexer();
//    _initTestOutput();
    _initHallIRQ();
    _initPixelIRQ();
}

void LED_control::_initTestOutput() {
    for (int pin=0; pin<16; pin++) {
        gpio_init(pin);										// set gpio as output
	    gpio_set_dir(pin, GPIO_OUT);								//
    }
}

void LED_control::_setTestOutput(bool status) {
    for (int pin=0; pin<8; pin++) gpio_put(pin, status);
    gpio_put(8,1);
    for (int pin=9; pin<16; pin++) gpio_put(pin,0);
}

void LED_control::_initMultiplexer(){

    // Load LED_MUX into this PIO's instruction memory.
 //   uint offset = pio_add_program(pio, &LED_MUX_program);
    uint offset = pio_add_program(pio, &LED_multiplexer_program);

    // initiate confic structures c
//    pio_sm_config c = LED_MUX_program_get_default_config(offset);
    pio_sm_config c = LED_multiplexer_program_get_default_config(offset);

    // Map the state machine's OUT pin group to pins 0, ..., 15
//    sm_config_set_out_pins(&c, 0, 16);
    sm_config_set_out_pins(&c, 0, 8);
    // map the SET pins to pin 15
//    sm_config_set_set_pins(&c, 15, 1);
    sm_config_set_set_pins(&c, 8, 3);
    // define status
    sm_config_set_mov_status (&c, STATUS_TX_LESSTHAN , 1 );   
    // Join TX FIFO
    sm_config_set_fifo_join	(&c, PIO_FIFO_JOIN_TX);	
    // Set pindir for all pins
    pio_sm_set_consecutive_pindirs(pio, sm, 0, 16, true);
    // set clk frequency to 130/50 MHz = 2.6 MHz. 31 wait cycles will correspond to 124 µs => works with "4"
    sm_config_set_clkdiv_int_frac(&c, 100, 0);  // 7 for LED_MUX

    // enable IRQ by setting IRQ0_INTE - interrupt enable register    pis_interrupt0 = PIO_INTR_SM0_LSB
    // this routes the PIO SM interrupts (IRQ0...IRQ7) to the system interrupts 7 and 8.
    pio_set_irq0_source_enabled(pio, pis_interrupt0 , true);
    //Set the handler in the NVIC. IRQ7 = PIO0_IRQ_0
    irq_set_exclusive_handler(7, _pioIRQ);  
    //enabling the PIO0_IRQ_0
    irq_set_enabled(7, true);   

    // Set this pin's GPIO function "pio"
    for (uint i=0; i<16; i++) pio_gpio_init(pio, i);

    // Load configuration to pio, and jump to the start of the program
    pio_sm_init(pio, sm, offset, &c);

    // Set the state machine running
    pio_sm_set_enabled(pio, sm, true);
}

void LED_control::_pioIRQ() {
    if (sublineCount<7) {
        pio_sm_put(pio, sm, subline[sublineCount][0]);       // push one full line to the pio
        pio_sm_put(pio, sm, subline[sublineCount][1]);  
//        pio_sm_put(pio, sm, subline[sublineCount][2]);  
//        pio_sm_put(pio, sm, subline[sublineCount][3]); 
        sublineCount++;
    }
    pio_interrupt_clear(pio, 0);                               // clear interrupt
}

void LED_control::_initHallIRQ() {
    gpio_init(Hall);
    gpio_set_dir(Hall, GPIO_IN);
    gpio_set_function(Hall, GPIO_FUNC_SIO);								// software IO control (SIO)

	gpio_set_irq_enabled_with_callback(Hall, GPIO_IRQ_EDGE_FALL, true, &_HallIRQ);    // attach HallRIQ

    pwm_clear_irq(0);										// clear pwm interrupt
	pwm_set_irq_enabled(0, true);							// enable pwm interrupt

} 

void LED_control::_HallIRQ(uint gpio, uint32_t events) {
    _tpt = _tpt + pwm_get_counter(0);

	long new_line_period = _tpt/_LPT;

	if (new_line_period>65500) new_line_period = 65500;

    long delta = labs(new_line_period - _line_period);
    if(delta<10) _line_period = (63*_line_period+new_line_period)/64;      // Otherwise make small corrections, only.
  	if((delta>=10)&&(delta<100)) _line_period = (15*_line_period+new_line_period)/16;
    if(delta>=100) _line_period = new_line_period;
    
  	pwm_set_wrap (0, _line_period);							      // upper threshold of counter 0

 	_tpt = 0;
  	_line_counter1 = _line_offset;  							  // restart line_counter
  	_line_counter0 = _line_offset + _LPT/2;

  	if (_line_counter0 >= _LPT) _line_counter0 = _line_counter0-_LPT;

}

void LED_control::_initPixelIRQ() {
    gpio_init(PWM0_A);										// set gpio as output
	gpio_set_dir(PWM0_A, true);								//

	gpio_set_function(PWM0_A, GPIO_FUNC_PWM);				// enable PWM pin

	pwm_set_wrap (0, _line_period);							// upper threshold of counter 0
	pwm_set_phase_correct (0, false);						// counter 0 will reset to 0, once upper threshold is reached
	
	pwm_set_clkdiv_int_frac(0, 2, 0);					    // set divisor for clock divider (system clock = 125 MHz)

	pwm_set_chan_level(0, 0, _line_period-1);			    // level is the mid threshold, when the output goes to zero

	pwm_set_enabled (0, true);								// enable PWM slice 0 (output pins 16 and 17)

	irq_set_exclusive_handler(PWM_IRQ_WRAP, _PixelIRQ);		// attach PixelIRQ() to the PWM interrupt
	irq_set_enabled(PWM_IRQ_WRAP, true);					// enanble irq

	_startPattern();
}

void LED_control::_PixelIRQ() {    
    _tpt+=_line_period;


    for (int sl = 0; sl<7; sl++) {                         // save all sublines for later
		for (int b = 3; b<7; b++) line_past[_line_counter0*7+sl][b] = line[_line_counter0*7+sl][b];
    }
    // a "line" consists of 56 LEDs from the center to the outside. 
    // The two halfs of the LED row display different lines (180 degrees in between)

    for (int sl = 0; sl<7; sl++) {
        uint8_t a0, a1, a2, a3, a4, a5, a6, a7;

        a0 = line[_line_counter0*7+sl][0];
        a1 = line[_line_counter0*7+sl][1];
        a2 = line[_line_counter0*7+sl][2];
        a3 = (line[_line_counter0*7+sl][3]&0x0F)|(line_past[_line_counter1*7+sl][3]&0xF0);
        a4 = line_past[_line_counter1*7+sl][4];
        a5 = line_past[_line_counter1*7+sl][5];
        a6 = line_past[_line_counter1*7+sl][6];
        a7 = 0x00;

        subline[sl][0]= (a3<< 24) + (a2 << 16) + (a1 << 8) + a0;
        subline[sl][1]= (a7 << 24) + (a6 << 16) + (a5 << 8) + a4;
    }

    pio_sm_put(pio, sm, subline[0][0]);       // push one full line to the pio
    pio_sm_put(pio, sm, subline[0][1]);  
    pio_sm_put(pio, sm, subline[1][0]);       // push one full line to the pio
    pio_sm_put(pio, sm, subline[1][1]);  
    
//    pio_sm_put(pio, sm, subline[0][2]);  
//    pio_sm_put(pio, sm, subline[0][3]);  

    sublineCount = 2;  //1

    _line_counter0++;
    if (_line_counter0 > (_LPT-1)) _line_counter0 = 0;	
	
    _line_counter1++;
    if (_line_counter1 > (_LPT-1)) _line_counter1 = 0;

	pwm_clear_irq(0);										// clear interrupt

}

void LED_control::_startPattern(){
    for (int ln=0; ln<240; ln++) {
        int bri = ln/30;                    // brightness values 0, .... 7

        for (int sl=0; sl<7; sl ++) {
            for (int b=0; b<7; b++) {
                if (bri>sl) line[ln*7+sl][b]=0xFF;
                else line[ln*7+sl][b]=0;
            }
        }
    }
}




