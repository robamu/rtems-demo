target_sources(${TARGET_NAME} PRIVATE
	init.c
	led.c
	main.cpp
)

add_subdirectory(boardconfig)