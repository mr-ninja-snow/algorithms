cmake_minimum_required(VERSION 2.8.11)

project(binary_search_tree)

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(ALL_FILES
	main.cpp
	binary_search_tree.cpp
	binary_search_tree.hpp
	catch.hpp
)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(${PROJECT_NAME} ${ALL_FILES})