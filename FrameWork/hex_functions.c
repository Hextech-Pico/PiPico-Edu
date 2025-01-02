#include <stdio.h>
#include <stdint.h>
#include "hex_functions.h"
#include "pico/stdlib.h"

// Second core code: core1_code
// Only writes the USB input to back to the terminal
void core1_code() {
    while (true) {
        sleep_ms(10);
        uint8_t command[COMMAND_LENGTH];
        uint16_t command_index = get_command(command);
        if (command_index > 0) {
            for (uint16_t i = 0; i < command_index; i++) {
                printf("%c", command[i]);
            }
        }
    }
}

// Reading the USB input and storing it in the buffer
uint16_t get_command(uint8_t *command) {
    uint16_t command_index = 0;
    while (true) {
        int c = getchar_timeout_us(0);
        if (c != PICO_ERROR_TIMEOUT && command_index < COMMAND_LENGTH) {
            command[command_index++] = (c & 0xFF);
        } else {
            break;
        }
    }
    return command_index;
}