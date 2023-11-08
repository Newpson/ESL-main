#include "esl_led.h"
#include "esl_button.h"
#include "nrf_delay.h"
#include "nrfx_gpiote.h"
#include "nrfx_systick.h"
#include "app_timer.h"

#define BUTTON_THRESHOLD_MS 200
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

volatile bool sleep = false;
APP_TIMER_DEF(timer_press);

void SW1_IRQHandler(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
	static int sw1_pcount = 0;
	++sw1_pcount;
	/* app_timer_stop(timer_press); */
	app_timer_start(timer_press, APP_TIMER_TICKS(BUTTON_THRESHOLD_MS), &sw1_pcount);
}

void TIMER_PRESS_IRQHandler(void *p_context)
{
	int *pcount = (int *) p_context;
	sleep = !sleep;
	/* switch (*pcount) */
	/* { */
	/* 	case 1: */
	/* 	case 2: */
	/* 		sleep = !sleep; */
	/* 		break; */
	/* } */
	*pcount = 0;
}

void led_toggle_linear(int led)
{
	for (int wait = 0; wait < BLINK_DCTIME_US; wait += BLINK_DCDELTA_US)
	{
		while (sleep)
		{
			__WFE();
		}
		esl_led_toggle(led);
		nrfx_systick_delay_us(wait);
		esl_led_toggle(led);
		nrfx_systick_delay_us(BLINK_DCTIME_US-wait);
	}
}

int main(void)
{
	/* timers */
	app_timer_init();
	nrfx_systick_init();

	app_timer_create(&timer_press, APP_TIMER_MODE_SINGLE_SHOT, TIMER_PRESS_IRQHandler);

	/* gpio */
	int blinkcnt[] = {BLINKCNT_0, BLINKCNT_1, BLINKCNT_2, BLINKCNT_3};
	int leds[] = {LED1, LED2_R, LED2_G, LED2_B};

	esl_leds_init();
	esl_button_init(SW1, SW1_IRQHandler);

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
