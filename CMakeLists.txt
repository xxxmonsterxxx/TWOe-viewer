##########################################################################

project(TWOe-viewer)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_BUILD_TYPE RelWithDebInfo)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

include_directories(include)

set(LTFD_DIR modules/libtinyfiledialogs)

file (GLOB SOURCES src/*.cpp)
list(APPEND SOURCES ${LTFD_DIR}/tinyfiledialogs.c)

add_executable(${PROJECT_NAME} ${SOURCES})

# additional libraries and headers

set(GLM_INC_DIR modules/glm)

message(STATUS ${LTFD_DIR})

find_package(Vulkan REQUIRED)
find_package(SGR 0.9.1 EXACT)
find_package(SGE 0.5.1 EXACT)

find_package(glfw3 3.3 REQUIRED)
get_target_property(GLFW3_INCLUDE_DIRS glfw INTERFACE_INCLUDE_DIRECTORIES)
include_directories(${GLFW3_INCLUDE_DIRS}/GLFW)

include_directories(${Vulkan_INCLUDE_DIRS} ${SGE_INCLUDE_DIRS} ${SGR_INCLUDE_DIRS} ${GLM_INC_DIR} ${LTFD_DIR})
target_link_libraries (${PROJECT_NAME} ${SGE_LIBRARIES} glfw)

file(COPY Resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

###########################################################################