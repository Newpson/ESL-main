include("nrf5")

add_subdirectory(led)
# add_subdirectory(button)
# add_subdirectory(timer)

add_executable(${CMAKE_PROJECT_NAME})

target_sources(${CMAKE_PROJECT_NAME}
	PRIVATE main.c)

nrf5_target(${CMAKE_PROJECT_NAME})

target_link_libraries(${CMAKE_PROJECT_NAME}
	PUBLIC
	# nrf5_nrfx_systick
	# nrf5_nrfx_timer
	esl_led
	# esl_button
	# esl_timer
	nrf5_nrfx_clock
	# nrf5_nrfx_rtc
	nrf5_app_timer_v2
	nrf5_app_util_platform
	nrf5_sortlist
	nrf5_atfifo
)
