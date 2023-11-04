include("nrf5")

add_subdirectory(led)
add_subdirectory(button)

add_executable(${CMAKE_PROJECT_NAME})

target_sources(${CMAKE_PROJECT_NAME}
	PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/main.c
)

nrf5_target(${CMAKE_PROJECT_NAME})

target_link_libraries(${CMAKE_PROJECT_NAME}
	PUBLIC
	nrf5_delay
	esl_led
	esl_button
)

