cmake_minimum_required(VERSION 3.16)

set(TARGET_NAME SchottenTotten)

project(
    ${TARGET_NAME}
    VERSION 1.0.0
    LANGUAGES CXX
    DESCRIPTION "In Schotten Totten, nine boundary stones lie between you and your opponent. In front of each, you build poker-like formations of three cards on a side."
    HOMEPAGE_URL "https://github.com/Dashstrom/SchottenTotten"
)

# Ignore warning : Manually-specified variables were not used by the project
set(IGNORE_ME "${CMAKE_BUILD_TYPE}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

#=================== INCLUSION OF Project Files ====================#
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})

file(GLOB_RECURSE SOURCES
    "${INCLUDE_DIR}/*.hpp"
    "${SOURCE_DIR}/*.cpp"
)

#=================== SETUP EXECTUABLE ====================#
if (WIN32)
    add_executable(${TARGET_NAME} WIN32 ${SOURCES})
else()
    add_executable(${TARGET_NAME} ${SOURCES})
endif()

if(MSVC)
    target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Add the target includes
target_include_directories(${TARGET_NAME} PRIVATE ${INCLUDE_DIR})
target_include_directories(${TARGET_NAME} PRIVATE ${SOURCE_DIR})

#===================== LINKING LIBRARIES =======================#
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

set_target_properties(${TARGET_NAME} PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

target_link_libraries(${TARGET_NAME} PRIVATE Qt6::Widgets)
