cmake_minimum_required(VERSION 3.16)

set(TARGET_NAME SchottenTotten)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

project(
  ${TARGET_NAME}
  VERSION 1.0.0
  LANGUAGES CXX
  DESCRIPTION "In Schotten Totten, nine boundary stones lie between you and your opponent. In front of each, you build poker-like formations of three cards on a side."
  HOMEPAGE_URL "https://github.com/Dashstrom/SchottenTotten"
)

# Ignore warning : Manually-specified variables were not used by the project
set(IGNORE_ME "${CMAKE_BUILD_TYPE}")

# Release by default
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Set MACOSX variable
#if(APPLE)
#  set(CMAKE_OSX_ARCHITECTURES "arm64")
#  set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13")
#endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
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
if (WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release")
  add_executable(${TARGET_NAME} WIN32 ${SOURCES})
else()
  add_executable(${TARGET_NAME} ${SOURCES})
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # using Clang
  target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using GCC
  if (WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
  else()
    target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -pedantic -Werror -Wredundant-decls -Wformat-security -Wformat-signedness -Wshadow -Wdouble-promotion -Wfloat-equal -pedantic-errors -fverbose-asm -gdwarf -fsanitize=leak)
  endif()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  # using Intel C++
  target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # using Visual Studio C++
  target_compile_options(${TARGET_NAME} PRIVATE /W3 /WX)
endif()

# Add the target includes
target_include_directories(${TARGET_NAME} PRIVATE ${INCLUDE_DIR})
target_include_directories(${TARGET_NAME} PRIVATE ${SOURCE_DIR})

#===================== LINKING LIBRARIES =======================#
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)


if (WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release")
  set_target_properties(${TARGET_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
  )
else()
  set_target_properties(${TARGET_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
  )
endif()

target_link_libraries(${TARGET_NAME} PRIVATE Qt6::Widgets)
