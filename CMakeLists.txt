# cmake needs this line
cmake_minimum_required(VERSION 3.1)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Define project name
set(NAME snake_gmae)
project(${NAME})

#Find Treads (keylock -> pthread.h)
#find_package (Threads)

# Find OpenCV
find_package(OpenCV REQUIRED)

#Linking
include_directories(./scr)

add_library(timer ./scr/timer.cpp)

add_library(segment	./scr/segment.cpp)
add_library(snake	./scr/snake.cpp)
add_library(rabbit	./scr/rabbit.cpp)
add_library(game	./scr/game.cpp)

#target_link_libraries(game		${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(game		${OpenCV_LIBS})
#target_link_libraries(game		keylock)
target_link_libraries(game		timer)

target_link_libraries(snake		segment)
target_link_libraries(rabbit	snake)
target_link_libraries(game		rabbit)

# Declare the executable target built from your sources
add_executable(main main.cpp)

# Link your application with OpenCV libraries
target_link_libraries(main game)
target_link_libraries(main ${OpenCV_LIBS})

