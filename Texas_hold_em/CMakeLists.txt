cmake_minimum_required(VERSION 2.6)

project(pokertest)

include_directories(${PROJECT_SOURCE_DIR}SDL2/include/SDL2)
link_directories(${PROJECT_SOURCE_DIR}/SDL2/lib/x86)

add_executable(

	testpoker
	
	src/main.cpp
	
)

target_link_libraries(testpoker SDL2main SDL2)