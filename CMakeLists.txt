##########################################################################

project(TWOe-viewer)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++17")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fobjc-arc -ObjC++")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_BUILD_TYPE RelWithDebInfo)

# find additional dependecies
find_package(glfw3 3.3 REQUIRED)

# define if glfw3 found
if (NOT glfw3_DIR)
	set(GLFW3_FOUND FALSE)
else (NOT glfw3_DIR)
	set(GLFW3_FOUND TRUE)
	get_target_property(GLFW_INC_DIR glfw INTERFACE_INCLUDE_DIRECTORIES)
endif (NOT glfw3_DIR)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

include_directories(include)

file (GLOB SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

set(GLM_INC_DIR modules/glm)
set(SGR_FOLDER ~/Programming/Library/SGR/0.6.0)
set(SGE_FOLDER ~/Programming/Library/SGE/0.2.0)

find_library(SGR_LIB SGR ${SGR_FOLDER}/lib/shared/)
find_library(SGE_LIB SGE ${SGE_FOLDER}/lib/shared/)

include_directories(${SGE_FOLDER}/include ${SGR_FOLDER}/include ${GLM_INC_DIR} ${GLFW_INC_DIR})
target_link_libraries (${PROJECT_NAME} ${SGE_LIB} ${SGR_LIB})

file(COPY Resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

###########################################################################