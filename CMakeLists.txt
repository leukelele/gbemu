cmake_minimum_required(VERSION 4.0.2)

project(gbemu C)

include_directories(include)

# Collect all .c files in the 'lib' directory
file(GLOB LIB CONFIGURE_DEPENDS "lib/*.c")

add_executable(${PROJECT_NAME}
	gbemu/main.c
	${LIB}
)
