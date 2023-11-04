#ifndef ESL_LED
#define ESL_LED

#include "nrf_gpio.h"

#define LED1 NRF_GPIO_PIN_MAP(0, 6)
#define LED2_R NRF_GPIO_PIN_MAP(0, 8)
#define LED2_G NRF_GPIO_PIN_MAP(1, 9)
#define LED2_B NRF_GPIO_PIN_MAP(0, 12)

int __esl_led_high(int led);

void esl_led_init(int led);

void esl_leds_init(void);

void esl_led_toggle(int led);

#endif /* ESL_LED */
