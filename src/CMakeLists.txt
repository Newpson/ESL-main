include("nrf5")

add_subdirectory(led)
add_subdirectory(button)

add_executable(${CMAKE_PROJECT_NAME})

target_sources(${CMAKE_PROJECT_NAME}
	PRIVATE main.c
)

nrf5_target(${CMAKE_PROJECT_NAME})

target_link_libraries(${CMAKE_PROJECT_NAME}
	PUBLIC
	nrf5_nrfx_systick
	nrf5_app_timer
	nrf5_app_util_platform
	esl_led
	esl_button
)
