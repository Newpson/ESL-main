cmake_minimum_required(VERSION 3.14)
project(esl LANGUAGES C ASM)

list(APPEND CMAKE_MODULE_PATH "./cmake")

include("nrf5")
add_executable(${CMAKE_PROJECT_NAME}
	"src/main.c"
)

nrf5_target("${CMAKE_PROJECT_NAME}")
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
	nrf5_nrfx_gpiote
	nrf5_boards
	nrf5_delay
)
