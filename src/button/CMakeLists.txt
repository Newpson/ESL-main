add_library(esl_button STATIC)

target_sources(esl_button
	PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/esl_button.c
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/esl_button.h
)

target_include_directories(esl_button
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(esl_button
	PUBLIC
	nrf5_nrfx_gpiote
)
