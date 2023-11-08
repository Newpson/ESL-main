add_library(esl_led STATIC)

target_sources(esl_led
	PRIVATE esl_led.c
	PUBLIC esl_led.h
)

target_include_directories(esl_led
	PUBLIC ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(esl_led
	PUBLIC nrf5_nrfx_gpiote
)
