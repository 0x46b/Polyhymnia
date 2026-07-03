#ifndef LED_DRIVER_H
#define LED_DRIVER_H
#include <stdint.h>

typedef enum {
  SAW_LED = 1,
  SQUARE_LED = 2,
  TRIANGLE_LED = 3,
  SINE_LED = 4
} led_register_state;

typedef struct {
  /* ShiftRegisterCLocK*/
  uint8_t SRCLK;
  /* Pin to SER of the shift-register ()*/
  uint8_t SER;
  /* (storage) RegisterCLocK*/
  uint8_t RCLK;
  volatile uint8_t *port;
} led_controller_config;

typedef struct {
  led_register_state register_state;
  led_controller_config config;
} led_controller_state;

void led_controller_configure(void);
void set_led_register_to(led_register_state state);
void led_controller_initialize(led_controller_config *config);
#endif
