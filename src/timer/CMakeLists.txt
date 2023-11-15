add_library(esl_timer STATIC)

target_sources(esl_timer
	PRIVATE esl_timer.c
	PUBLIC esl_timer.h
)

target_include_directories(esl_timer
	PUBLIC ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(esl_timer
	PUBLIC nrf5_nrfx_timer
)
