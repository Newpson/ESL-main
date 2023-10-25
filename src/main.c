#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "boards.h"

#define DELAY 500
#define DEVICE_ID 6598

#define BLINKCNT_0 ((DEVICE_ID)/1000)
#define BLINKCNT_1 ((DEVICE_ID)/100%10)
#define BLINKCNT_2 ((DEVICE_ID)/10%10)
#define BLINKCNT_3 ((DEVICE_ID)/10%10)

static inline
void blink(uint8_t led, int8_t cnt)
{
	for (; cnt > 0; --cnt)
	{
		bsp_board_led_invert(led);
		nrf_delay_ms(DELAY);
		bsp_board_led_invert(led);
		nrf_delay_ms(DELAY);
	}
}

int main(void)
{
	bsp_board_init(BSP_INIT_LEDS);
	int8_t blinkcnt[] = {BLINKCNT_0, BLINKCNT_1, BLINKCNT_2, BLINKCNT_3};

	while (true)
	{
		for (int8_t i = 0; i < 4; ++i)
		{
			blink(i, blinkcnt[i]);
			nrf_delay_ms(4*DELAY);
		}
	}
}
