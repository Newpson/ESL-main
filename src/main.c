#include "esl_led.h"
#include "esl_button.h"
#include "esl_timer.h"
#include "nrfx_timer.h"
#include "nrfx_gpiote.h"
#include "nrfx_systick.h"

#define BUTTON_BOUNCE_MS 10
#define BUTTON_PRESS_MS 350
#define BLINK_DELAY_MS 500
#define BLINK_DCTIME_MS 1 /* PWM duty cycle time */
#define BLINK_DCTIME_US 1000*BLINK_DCTIME_MS
#define BLINK_DCCOUNT BLINK_DELAY_MS/BLINK_DCTIME_MS
#define BLINK_DCDELTA_US BLINK_DCTIME_US/BLINK_DCCOUNT
#define DEVICE_ID 6598

#define BLINKCNT_0 ((DEVICE_ID)/1000)
#define BLINKCNT_1 ((DEVICE_ID)/100%10)
#define BLINKCNT_2 ((DEVICE_ID)/10%10)
#define BLINKCNT_3 ((DEVICE_ID)%10)

volatile bool wait = false;
volatile int press_count = 0;
const nrfx_timer_t SW1_bounce_timer = NRFX_TIMER_INSTANCE(0);
const nrfx_timer_t SW1_press_timer = NRFX_TIMER_INSTANCE(1);

void SW1_press_timer_handler(nrf_timer_event_t event_type, void *p_context)
{
	nrfx_timer_disable(&SW1_press_timer);
	switch (press_count)
	{
		case 2:
			wait = !wait;
			break;
		default:
			break;
	}
	press_count = 0;
}

void SW1_bounce_timer_handler(nrf_timer_event_t event_type, void *p_context)
{
	nrfx_timer_disable(&SW1_bounce_timer);
	++press_count;
	esl_timer_reset(&SW1_press_timer);
}

void SW1_action_handler(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
	esl_timer_reset(&SW1_bounce_timer);
}

void led_blink_pwm(int led, int wait_us)
{
	esl_led_toggle(led);
	nrfx_systick_delay_us(wait_us);
	esl_led_toggle(led);
	nrfx_systick_delay_us(BLINK_DCTIME_US-wait_us);
}

void led_toggle_linear(int led)
{
	for (int wait_us = 0; wait_us < BLINK_DCTIME_US; wait_us += BLINK_DCDELTA_US)
	{
		if (wait)
		{
			while (wait)
			{
				led_blink_pwm(led, wait_us);
			}
		}
		else
		{
			led_blink_pwm(led, wait_us);
		}
	}
}

int main(void)
{
	esl_timer_init(&SW1_bounce_timer, BUTTON_BOUNCE_MS, SW1_bounce_timer_handler);
	esl_timer_init(&SW1_press_timer, BUTTON_PRESS_MS, SW1_press_timer_handler);
	nrfx_systick_init();
	esl_leds_init();
	esl_button_init(SW1, SW1_action_handler);

	int blinkcnt[] = {BLINKCNT_0, BLINKCNT_1, BLINKCNT_2, BLINKCNT_3};
	int leds[] = {LED1, LED2_R, LED2_G, LED2_B};

	while (true)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int b = blinkcnt[i]; b > 0; --b)
			{
				led_toggle_linear(leds[i]);
				esl_led_toggle(leds[i]);
				led_toggle_linear(leds[i]);
				esl_led_toggle(leds[i]);
			}
			/* break between blink series */
			nrfx_systick_delay_ms(4*BLINK_DELAY_MS);
		}
	}
	return 0;
}
