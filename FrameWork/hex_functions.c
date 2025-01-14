#include <stdio.h>
#include <stdint.h>
#include "hex_functions.h"
#include "pico/bootrom.h" 
#include "pico/stdlib.h"
#include "hardware/adc.h"


// Second core code: core1_code
// Only writes the USB input to back to the terminal
void core1_code() {
    while (true) {
        uint8_t command[COMMAND_LENGTH];
        uint64_t command_value = get_command(command);
        uint16_t adc_values[3];
        //printf("1. The command value: %llu\n", command_value);
        //sleep_ms(10);
        switch (command_value)
        {
        case TEMP:
            adc_set_temp_sensor_enabled(true); // Power up the temperature sensor
            adc_select_input(4);               // Select ADC channel 4
            float temperature = read_onboard_temperature();
            printf("Onboard temperature = %.02f C\n", temperature);
            adc_set_temp_sensor_enabled(false); // Power down the temperature sensor
            break;

        case NOCOMM:
            break;

        case REBOOT:
            printf("Rebooting...\n");
            sleep_ms(1000);
            rom_reset_usb_boot(0, 0);
            break;
        
        case TELEM:
            read_adc_values(adc_values);
            printf("ADC0: %d\n", adc_values[0]);
            printf("ADC1: %d\n", adc_values[1]);
            printf("ADC2: %d\n", adc_values[2]);
            break;
        case UPTIME:
            printf("Uptime: %d\n", 0);
            break;
            
        default:
            printf("Unknown command\n Value: %d\n Value Hex: %x\n", command_value, command_value);
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
        //printf("1. point c: %d\n", c);
        if (c != PICO_ERROR_TIMEOUT) {
            if (c == '\n' || c == '\r') {
                // Found CRLF, treat as end of command
                break;
            }
            command[command_index++] = (c & 0xFF);  // Store ASCII value in command array
            result = (result << 8) | (unsigned char)c;  // Shift and append ASCII value to result
            //for debugging
            //printf("2. point c: %llu\n", result);  // Print result (use %llu for 64-bit)
        }
        //sleep_ms(1); // Sleep for 0.1 second, adjust if needed
    }

    return result;  // Return the concatenated 64-bit number
}


/* References for this implementation:
 * raspberry-pi-pico-c-sdk.pdf, Section '4.1.1. hardware_adc'
 * pico-examples/adc/adc_console/adc_console.c */
float read_onboard_temperature() {
    
    /* 12-bit conversion, assume max value == ADC_VREF == 3.3 V */
    const float conversionFactor = 3.3f / (1 << 12);
    float adc = (float)adc_read() * conversionFactor;
    float tempC = 27.0f - (adc - 0.706f) / 0.001721f;

    return tempC;
}

// Function to read ADC channels into a provided array
void read_adc_values(uint16_t *adc_values) {
    // Initialize ADC hardware
    adc_init();

    // Enable ADC GPIOs
    adc_gpio_init(26); // ADC0 (GPIO26)
    adc_gpio_init(27); // ADC1 (GPIO27)
    adc_gpio_init(28); // ADC2 (GPIO28)

    // Loop through the channels and read values
    for (size_t i = 0; i < 3; i++) {
        adc_select_input(i);         // Select ADC channel (0, 1, 2)
        adc_values[i] = adc_read(); // Read raw value into the array
    }
}