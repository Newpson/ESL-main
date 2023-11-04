#include "esl_led.h"
#include "nrf_gpio.h"

int __esl_led_high(int led)
{
	switch (led)
	{
		case LED1:
		case LED2_R:
		case LED2_G:
		case LED2_B:
			return 0;
		default:
			return 1;
	}
}

void esl_led_init(int led)
{
	nrf_gpio_cfg_output(led);
	nrf_gpio_pin_write(led, !__esl_led_high(led));
}

void esl_leds_init(void)
{
	esl_led_init(LED1);
	esl_led_init(LED2_R);
	esl_led_init(LED2_G);
	esl_led_init(LED2_B);
}

void esl_led_toggle(int led)
{
	nrf_gpio_pin_toggle(led);
}
