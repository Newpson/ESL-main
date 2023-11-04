#include "esl_button.h"
#include "nrf_gpio.h"
#include <stdbool.h>

int __esl_button_pull(int button)
{
	switch (button)
	{
		case SW1:
			return NRF_GPIO_PIN_PULLUP;
		default:
			return NRF_GPIO_PIN_NOPULL;
	}
}

void esl_button_init(int button)
{
	nrf_gpio_cfg_input(button, __esl_button_pull(button));
}

void esl_buttons_init()
{
	esl_button_init(SW1);
}

bool esl_button_pressed(int button)
{
	return nrf_gpio_pin_read(button) != (__esl_button_pull(button) == NRF_GPIO_PIN_PULLUP);
}
