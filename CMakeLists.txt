cmake_minimum_required(VERSION 4.0.2)

project(gbemu C)

# produces a compile_commands.json for clangd lsp
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set c std
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# global compiler flags
add_compile_options(-Wall -Werror -Wpedantic)

# include header files
include_directories(include)

# collect all .c files in the 'lib' directory
file(GLOB LIB CONFIGURE_DEPENDS "lib/*.c")

# define executable target
add_executable(gbemu
	gbemu/main.c
	${LIB}
)

# collect all .c files in the 'test' directory
file(GLOB TEST CONFIGURE_DEPENDS "test/*.c")

# def Unity static library
add_library(unity STATIC
  external/Unity/src/unity.c
)

# def test executable
add_executable(tests
	${TEST}
	${LIB}
)

# only the tests target itself will use include directory when compiling
target_include_directories(tests PRIVATE 
	${CMAKE_SOURCE_DIR}/external/Unity/src)

# link unity to test executable
target_link_libraries(tests PRIVATE unity)

# enable testing
enable_testing()

# add test
add_test(NAME UnitTests COMMAND tests)
