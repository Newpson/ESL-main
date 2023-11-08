cmake_minimum_required(VERSION 3.27)

set(CMAKE_TOOLCHAIN_FILE
	${CMAKE_CURRENT_LIST_DIR}/cmake/arm-none-eabi.cmake)

set(NRF5_BOARD pca10059)
set(NRF5_TARGET nrf52840_xxaa)
set(NRF5_SOFTDEVICE_VARIANT s113)
set(NRF5_SDK_PATH
	/opt/nrf5-sdk_16.0.0)
set(NRF5_SDKCONFIG_PATH
	${CMAKE_CURRENT_LIST_DIR})
set(NRF5_LINKER_SCRIPT
	${CMAKE_CURRENT_LIST_DIR}/nrf52840.ld)

list(APPEND CMAKE_MODULE_PATH
	${CMAKE_CURRENT_LIST_DIR}/cmake)

project(esl LANGUAGES C ASM)

add_subdirectory(src)

# enable_testing()
# add_subdirectory(tests)
