cmake_minimum_required(VERSION 4.0.2)

project(gbemu C)

# include header files
include_directories(include)

# collect all .c files in the 'lib' directory
file(GLOB LIB CONFIGURE_DEPENDS "lib/*.c")

# add compiler flags globally for all C files
add_compile_options(-Wall -Werror -Wpedantic)

# define executable target
add_executable(${PROJECT_NAME}
	gbemu/main.c
	${LIB}
)
