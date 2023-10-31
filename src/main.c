#include "boards.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include <stdbool.h>

#define SW1 NRF_GPIO_PIN_MAP(1, 6)

/* #define LED1 NRF_GPIO_PIN_MAP(0, 6) */
/* #define LED2_R NRF_GPIO_PIN_MAP(0, 8) */
/* #define LED2_G NRF_GPIO_PIN_MAP(1, 9) */
/* #define LED2_B NRF_GPIO_PIN_MAP(0, 12) */

#define DELAY 500
#define DEVICE_ID 6598

#define BLINKCNT_0 ((DEVICE_ID)/1000)
#define BLINKCNT_1 ((DEVICE_ID)/100%10)
#define BLINKCNT_2 ((DEVICE_ID)/10%10)
#define BLINKCNT_3 ((DEVICE_ID)%10)

static inline
void blink(const int8_t led, int8_t cnt)
{
	for (; cnt > 0; --cnt)
	{
		/* pull-up, waiting until 0 */
		while (nrf_gpio_pin_read(SW1));
		bsp_board_led_invert(led);
		nrf_delay_ms(DELAY);
		while (nrf_gpio_pin_read(SW1));
		bsp_board_led_invert(led);
		nrf_delay_ms(DELAY);
	}
}

int main(void)
{
	int8_t blinkcnt[] = {BLINKCNT_0, BLINKCNT_1, BLINKCNT_2, BLINKCNT_3};

	bsp_board_init(BSP_INIT_LEDS);
	nrf_gpio_cfg_input(SW1, NRF_GPIO_PIN_PULLUP);

	while (true)
	{
		for (int8_t i = 0; i < 4; ++i)
		{
			blink(i, blinkcnt[i]);
			nrf_delay_ms(4*DELAY);
		}
	}
}
