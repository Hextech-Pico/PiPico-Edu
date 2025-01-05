#include <stdio.h>
#include <stdint.h>
#include "hex_functions.h"
#include "pico/stdlib.h"

// Second core code: core1_code
// Only writes the USB input to back to the terminal
void core1_code() {
    while (true) {
        uint8_t command[COMMAND_LENGTH];
        uint64_t command_value = get_command(command);
        printf("1. The command value: %llu\n", command_value);
        sleep_ms(1000);
        switch (command_value)
        {
        case TEMP:
            printf("Temperature: %d C \n");
            break;

        case NOCOMM:
            break;

        case REBOOT:
            printf("Rebooting...\n");
            sleep_ms(1000);
            //reset_usb_boot(0, 0);
            break;

        default:
            printf("Unknown command\n Value: %d\n", command_value);
            break;
        }
    }
}

uint64_t get_command(uint8_t *command) {
    uint16_t command_index = 0;
    uint64_t result = 0; // This will store the concatenated number

    while (command_index < COMMAND_LENGTH) {
        int c = getchar_timeout_us(0);
        //for debugging
        printf("1. point c: %d\n", c);
        if (c != PICO_ERROR_TIMEOUT) {
            if (c == '\n' || c == '\r') {
                // Found CRLF, treat as end of command
                break;
            }
            command[command_index++] = (c & 0xFF);  // Store ASCII value in command array
            result = (result << 8) | (unsigned char)c;  // Shift and append ASCII value to result
            //for debugging
            printf("2. point c: %llu\n", result);  // Print result (use %llu for 64-bit)
        }
        sleep_ms(1000); // Sleep for 1 second, adjust if needed
    }

    return result;  // Return the concatenated 64-bit number
}