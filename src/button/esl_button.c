#include "esl_button.h"
#include "nrfx_gpiote.h"
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

void esl_button_init(int button, nrfx_gpiote_evt_handler_t handler)
{
	if (!nrfx_gpiote_is_init())
	{
		nrfx_gpiote_init();
	}

	nrfx_gpiote_in_config_t conf = NRFX_GPIOTE_CONFIG_IN_SENSE_TOGGLE(true);
	conf.pull = __esl_button_pull(button);
	conf.sense = conf.pull == NRF_GPIO_PIN_PULLUP ? NRF_GPIOTE_POLARITY_LOTOHI : NRF_GPIOTE_POLARITY_HITOLO;
	
	nrfx_gpiote_in_init(button, &conf, handler);
	nrfx_gpiote_in_event_enable(button, true);
}

/* void esl_buttons_init() */
/* { */
/* 	esl_button_init(SW1); */
/* } */

bool esl_button_pressed(int button)
{
	return nrf_gpio_pin_read(button) != (__esl_button_pull(button) == NRF_GPIO_PIN_PULLUP);
}
