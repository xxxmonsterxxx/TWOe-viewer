##########################################################################

project(TWOe-viewer)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_BUILD_TYPE RelWithDebInfo)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

include_directories(include)

file (GLOB SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

# additional libraries and headers

set(GLM_INC_DIR modules/glm)

find_path(SGR_INC_DIR SGR/SGR.h)

find_library(SGE_LIB SGE)
find_path(SGE_INC_DIR SGE/SGE.h)

include_directories(${SGE_INC_DIR} ${SGR_INC_DIR} ${GLM_INC_DIR})
target_link_libraries (${PROJECT_NAME} ${SGE_LIB})

file(COPY Resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

###########################################################################