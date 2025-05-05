##########################################################################

cmake_minimum_required(VERSION 3.10)

project(TWOe-viewer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")

add_definitions(-DNDBUG=true)
set(CMAKE_BUILD_TYPE Release)
    
# set(CMAKE_BUILD_TYPE RelWithDebInfo)
# add_definitions(-DNDBUG=false)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

include_directories(include)

set(LTFD_DIR modules/libtinyfiledialogs)

find_package(Vulkan REQUIRED)
find_package(SGR 0.11.1 EXACT)
find_package(SGE 0.7.0 EXACT)

find_package(glfw3 3.3 REQUIRED)
get_target_property(GLFW3_INCLUDE_DIRS glfw INTERFACE_INCLUDE_DIRECTORIES)

file (GLOB SOURCES src/*.cpp)
list(APPEND SOURCES ${LTFD_DIR}/tinyfiledialogs.c)

if (APPLE AND CMAKE_BUILD_TYPE STREQUAL "Release")
    set(MACOSX_BUNDLE TRUE)

    file(GLOB_RECURSE RESOURCE_FILES "Resources/*")
    foreach (FILE ${RESOURCE_FILES})
        file(RELATIVE_PATH NEW_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${FILE})
        get_filename_component(NEW_FILE_PATH ${NEW_FILE} DIRECTORY)
        set_source_files_properties(${FILE}
                                    PROPERTIES
                                    MACOSX_PACKAGE_LOCATION "Resources/${NEW_FILE_PATH}"
                                    HEADER_FILE_ONLY ON)
    endforeach()

    set(MACOSX_BUNDLE_ICON_FILE "Logo/icon.icns")

    # install rpath for distributing
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    set(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")

    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SOURCES}
                                                 ${RESOURCE_FILES})

    set_target_properties(${PROJECT_NAME} PROPERTIES
                                        MACOSX_BUNDLE TRUE
                                        MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
                                        MACOSX_BUNDLE_BUNDLE_VERSION 1
                                        MACOSX_BUNDLE_SHORT_VERSION_STRING 0.9
                                        MACOSX_BUNDLE_COPYRIGHT "© 2022 SimpleGraphicsFam. All rights reserved.")

    set(BUNDLE_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.app)
    set(FRAMEWORKS_PATH ${BUNDLE_PATH}/Contents/Frameworks)

    file(COPY ${Vulkan_LIBRARIES} DESTINATION ${FRAMEWORKS_PATH} FOLLOW_SYMLINK_CHAIN)
    file(COPY $ENV{VULKAN_SDK}/lib/libMoltenVK.dylib DESTINATION ${FRAMEWORKS_PATH} FOLLOW_SYMLINK_CHAIN)
    file(COPY ${SGR_LIBRARIES} DESTINATION ${FRAMEWORKS_PATH} FOLLOW_SYMLINK_CHAIN)
    file(COPY ${SGE_LIBRARIES} DESTINATION ${FRAMEWORKS_PATH} FOLLOW_SYMLINK_CHAIN)
    file(COPY ${GLFW3_INCLUDE_DIRS}/../lib/libglfw.dylib DESTINATION ${FRAMEWORKS_PATH} FOLLOW_SYMLINK_CHAIN)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD                    
                        COMMAND codesign --deep --force --verbose --sign - ${BUNDLE_PATH}
                        COMMENT "Signing the application bundle...")
else ()
    add_executable(${PROJECT_NAME} ${SOURCES})
    file(COPY Resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif ()

# additional libraries and headers

set(GLM_INC_DIR modules/glm)
include_directories(${GLFW3_INCLUDE_DIRS}/GLFW)

include_directories(${Vulkan_INCLUDE_DIRS} ${SGE_INCLUDE_DIRS} ${SGR_INCLUDE_DIRS} ${GLM_INC_DIR} ${LTFD_DIR})
target_link_libraries (${PROJECT_NAME} ${SGE_LIBRARIES})

###########################################################################