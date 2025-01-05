#ifndef HEX_FUNCTIONS_H
#define HEX_FUNCTIONS_H

#include <stdint.h>  // For uint8_t, uint16_t

// Define COMMAND_LENGTH if not defined elsewhere
#ifndef COMMAND_LENGTH
#define COMMAND_LENGTH 8
#endif

// Define COMMANDS
#define TEMP 0x54454D50
#define REBOOT 0x5245424F
#define NOCOMM 0x00000000

// Wrapper function for the second core. This will handle the USB input.
void core1_code();

// Reading a char from the USB input and storing in a buffer.
// It returns the number according to the characters read.
uint64_t get_command(uint8_t *command);

// Command selection required.

#endif // HEX_FUNCTIONS_H