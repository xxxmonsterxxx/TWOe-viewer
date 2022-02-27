##########################################################################

project(TWOe-viewer)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++17")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fobjc-arc -ObjC++")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_BUILD_TYPE RelWithDebInfo)

find_package(glfw3 3.3 REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

include_directories(include)

# file(GLOB SOURCES	src/main.cpp
# 					src/TwoeViewer.cpp
# 					src/MainViewWidget.cpp)
file (GLOB SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

set(GLM_INC_DIR modules/glm)
set(SGR_FOLDER ~/Programming/Library/SGR/0.6.0)
set(SGE_FOLDER ~/Programming/Library/SGE/0.2.0)

find_library(SGR_LIB SGR ${SGR_FOLDER}/lib/shared/)
find_library(SGE_LIB SGE ${SGE_FOLDER}/lib/shared/)

include_directories(${SGE_FOLDER}/include ${SGR_FOLDER}/include ${GLM_INC_DIR})
target_link_libraries (${PROJECT_NAME} glfw ${SGE_LIB} ${SGR_LIB})

file(COPY Resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

###########################################################################