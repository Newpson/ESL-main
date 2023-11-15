#include "esl_timer.h"
#include "nrfx_timer.h"
#include <stdbool.h>

void esl_timer_init(
		nrfx_timer_t const *const instance,
		uint32_t time_ms,
		nrfx_timer_event_handler_t handler)
{
	nrfx_timer_init(instance, &(nrfx_timer_config_t)NRFX_TIMER_DEFAULT_CONFIG, handler);
	nrfx_timer_extended_compare(instance, NRF_TIMER_CC_CHANNEL0, nrfx_timer_ms_to_ticks(instance, time_ms), NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, true);
}

void esl_timer_reset(nrfx_timer_t const *const instance)
{
	nrfx_timer_disable(instance);
	nrfx_timer_clear(instance);
	nrfx_timer_enable(instance);
}
