#include "esl_led.h"
#include "esl_button.h"
#include "nrf_delay.h"

#define DELAY_MS 500
#define DEVICE_ID 6598

#define BLINKCNT_0 ((DEVICE_ID)/1000)
#define BLINKCNT_1 ((DEVICE_ID)/100%10)
#define BLINKCNT_2 ((DEVICE_ID)/10%10)
#define BLINKCNT_3 ((DEVICE_ID)%10)

int main(void)
{
	int blinkcnt[] = {BLINKCNT_0, BLINKCNT_1, BLINKCNT_2, BLINKCNT_3};
	int leds[] = {LED1, LED2_R, LED2_G, LED2_B};

	esl_leds_init();
	esl_buttons_init();

	while (true)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int b = blinkcnt[i]; b > 0; --b)
			{
				/* blink while the button is pressed */
				for (int c = 0; c < 2; ++c)
				{
					while (!esl_button_pressed(SW1));
					esl_led_toggle(leds[i]);
					nrf_delay_ms(DELAY_MS);
				}
			}
			/* break between blink series */
			nrf_delay_ms(4*DELAY_MS);
		}
	}
	return 0;
}
