#ifndef HEX_FUNCTIONS_H
#define HEX_FUNCTIONS_H

#include <stdint.h>  // For uint8_t, uint16_t

// Define COMMAND_LENGTH if not defined elsewhere
#ifndef COMMAND_LENGTH
#define COMMAND_LENGTH 8
#endif

// Wrapper function for the second core. This will handle the USB input.
void core1_code();

// Reading the USB input and storing it in the command buffer It returns the number of characters read.
uint16_t get_command(uint8_t *command);

#endif // HEX_FUNCTIONS_H