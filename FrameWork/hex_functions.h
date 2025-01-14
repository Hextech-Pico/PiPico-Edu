#ifndef HEX_FUNCTIONS_H
#define HEX_FUNCTIONS_H

#include <stdint.h>  // For uint8_t, uint16_t

// Define COMMAND_LENGTH if not defined elsewhere
#ifndef COMMAND_LENGTH
#define COMMAND_LENGTH 8
#endif

// Define COMMANDS
#define TEMP 0x54454D50
#define REBOOT 90457418714964
#define NOCOMM 0x00000000
#define UPTIME 9101002754575685 //need implementation
#define SLEEP 357761893712 //need implementation
#define WIFIID 0x574946494449 //need implementation
#define WIFIPW 0x574946495057 //need implementation
#define BTID 0x4254494449 //need implementation
#define BTPW 0x42545057 //need implementation
#define TELEM 0x54454C454D //need implementation



// Wrapper function for the second core. This will handle the USB input.
void core1_code();

// Reading a char from the USB input and storing in a buffer.
// It returns the number according to the characters read.
uint64_t get_command(uint8_t *command);

// Reading the onboard temperature sensor from examples
float read_onboard_temperature();
// Reading ADC values
void read_adc_values(uint16_t *adc_values);


// Command selection required.

#endif // HEX_FUNCTIONS_H