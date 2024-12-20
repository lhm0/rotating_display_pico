// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// --------------- //
// LED_multiplexer //
// --------------- //

#define LED_multiplexer_wrap_target 0
#define LED_multiplexer_wrap 25

static const uint16_t LED_multiplexer_program_instructions[] = {
            //     .wrap_target
    0x80a0, //  0: pull   block                      
    0x6008, //  1: out    pins, 8                    
    0xea00, //  2: set    pins, 0                [10]
    0xe007, //  3: set    pins, 7                    
    0x6008, //  4: out    pins, 8                    
    0xea01, //  5: set    pins, 1                [10]
    0xe007, //  6: set    pins, 7                    
    0x6008, //  7: out    pins, 8                    
    0xea02, //  8: set    pins, 2                [10]
    0xe007, //  9: set    pins, 7                    
    0x6008, // 10: out    pins, 8                    
    0xea03, // 11: set    pins, 3                [10]
    0xe007, // 12: set    pins, 7                    
    0x80a0, // 13: pull   block                      
    0xa025, // 14: mov    x, status                  
    0x0031, // 15: jmp    !x, 17                     
    0xc000, // 16: irq    nowait 0                   
    0x6008, // 17: out    pins, 8                    
    0xea04, // 18: set    pins, 4                [10]
    0xe007, // 19: set    pins, 7                    
    0x6008, // 20: out    pins, 8                    
    0xea05, // 21: set    pins, 5                [10]
    0xe007, // 22: set    pins, 7                    
    0x6008, // 23: out    pins, 8                    
    0xea06, // 24: set    pins, 6                [10]
    0xe007, // 25: set    pins, 7                    
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program LED_multiplexer_program = {
    .instructions = LED_multiplexer_program_instructions,
    .length = 26,
    .origin = -1,
};

static inline pio_sm_config LED_multiplexer_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + LED_multiplexer_wrap_target, offset + LED_multiplexer_wrap);
    return c;
}
#endif
