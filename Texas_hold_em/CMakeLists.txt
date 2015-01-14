########################
# Florent Baudon
########################

cmake_minimum_required(VERSION 2.6)

project(pokertest)

set(EXECUTABLE_OUTPUT_PATH bin/)

file(

        GLOB_RECURSE

        source_files

        src/*
)

add_executable(

	testpoker
	
	${source_files}
	
)

TARGET_LINK_LIBRARIES(testpoker pthread)