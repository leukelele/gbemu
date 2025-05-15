cmake_minimum_required(VERSION 4.0.2)

project(gbemu C)

include_directories(include)

add_executable(${PROJECT_NAME}
	gbemu/main.c
)
