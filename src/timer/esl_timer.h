#ifndef ESL_TIMER
#define ESL_TIMER

#include "nrfx_timer.h"
#include <stdint.h>

void esl_timer_init(
		nrfx_timer_t const *const instance,
		uint32_t time_ms,
		nrfx_timer_event_handler_t handler);

void esl_timer_reset(nrfx_timer_t const *const instance);

#endif /* ESL_TIMER */
