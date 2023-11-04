#ifndef ESL_BUTTON
#define ESL_BUTTON

#include "nrf_gpio.h"
#include <stdbool.h>

#define SW1 NRF_GPIO_PIN_MAP(1, 6)

int __esl_button_pull(int button);

void esl_button_init(int button);

void esl_buttons_init();

bool esl_button_pressed(int button);

#endif /* ESL_BUTTON */
