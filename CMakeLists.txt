cmake_minimum_required(VERSION 3.10.0)
project(iPaint VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(iPaint
    src/main.cpp
    src/glad/glad.c
    src/microtar/microtar.c
 "src/Network.cpp")

find_package(OpenAL CONFIG REQUIRED)
target_link_libraries(iPaint PRIVATE OpenAL::OpenAL)
	
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(iPaint PRIVATE glfw)

find_package(libwebsockets CONFIG REQUIRED)
target_link_libraries(iPaint PRIVATE websockets_shared)