#ifndef CONFIG_H
#define CONFIG_H

/***** PIN SELECTION FOR DISPLAY **/
#define PIN_SCK 27   // mandatory
#define PIN_MISO 1   // mandatory
#define PIN_MOSI 26  // mandatory
#define PIN_DC 38    // mandatory, can be any pin but using pin 0 (or 38 on T4.1) provides greater performance

#define PIN_CS 30          // optional (but recommended), can be any pin.
#define PIN_RESET 29       // optional (but recommended), can be any pin.
#define PIN_BACKLIGHT 32   // optional, set this only if the screen LED pin is connected directly to the Teensy.
#define PIN_TOUCH_IRQ 255  // optional, set this only if the touchscreen is connected on the same SPI bus
#define PIN_TOUCH_CS 255   // optional, set this only if the touchscreen is connected on the same spi bus

/* Pin Selection for buttons */
#define LEFT_BTN 3
#define ENTER_BTN 2
#define RIGHT_BTN 4
#define ENCODER_PIN1 8
#define ENCODER_PIN2 9

// SD Card CS Pin
#define SD_CS BUILTIN_SDCARD

/* LVGL-related configs */
// 40MHz SPI. Can do much better with short wires
#define SPI_SPEED 40000000

// screen size in portrait mode
#define LX 320
#define LY 240

// number of lines in lvgl's internal draw buffer
#define BUF_LY 40
#endif