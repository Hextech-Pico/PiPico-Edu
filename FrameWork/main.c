// This project is a frame for future projects. It uses Raspberry Pi Pico 2 W. RP2350 and Infineon CYW43439.
// The frame contains the initialization of the CYW43439 module and the initialization of the Pico 2 W board.
// Also contains the most common libraries.

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "pico/cyw43_arch.h"
#include "pico/multicore.h"
#include "hex_functions.h"  //own functions

int main() {
    stdio_init_all();                   // initialize the standard I/O library
    cyw43_arch_init();                  // initialize the CYW43439 module, wifi, bluetooth, onboard LED
    multicore_launch_core1(core1_code); // launch the core1_code function on the second core

    while (true) {
        // This is a simple blink, to check the first core is working
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, true);
        sleep_ms(1000);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, false);
        sleep_ms(1000);
    } 
}

