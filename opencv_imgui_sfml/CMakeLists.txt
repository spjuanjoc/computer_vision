cmake_minimum_required(VERSION 3.15)

project(opencv_imgui_sfml
  VERSION "1.0.0"
  DESCRIPTION "Hello OpenCV with ImGui and SFML"
  LANGUAGES CXX
)

# Options
option(ENABLE_WERROR   "Treat compiler warnings as errors" False)


# GLOB source files
file(GLOB_RECURSE
  SOURCE_FILES
    include/bindings/*.cpp
    src/*.cpp
    src/main.cpp
)


## Set the project as an executable target
add_executable(${PROJECT_NAME} ${SOURCE_FILES})


## Compiler options
include(cmake/CompilerOptions.cmake)
set_compiler_options(${PROJECT_NAME})


## Setup Conan < 2.0
if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD
    "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
    "${CMAKE_BINARY_DIR}/conan.cmake"
  )
endif ()


include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_autodetect(settings)
conan_check(REQUIRED)
conan_cmake_run(CONANFILE conanfile.txt
  BASIC_SETUP NO_OUTPUT_DIRS
  BUILD missing
  SETTINGS ${settings}
)


## Find third-party packages
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_BINARY_DIR})
find_package(argparse REQUIRED)
find_package(fmt      REQUIRED)
find_package(imgui    REQUIRED)
find_package(OpenCV   REQUIRED)
find_package(SFML     REQUIRED)
find_package(sigc++-3 REQUIRED)
find_package(spdlog   REQUIRED)


## Target
target_include_directories(${PROJECT_NAME}
  SYSTEM PRIVATE # These directories must be placed before other non-system directories
    ${argparse_INCLUDE_DIRS}
    ${imgui_INCLUDE_DIRS}
    ${opencv_INCLUDES}
    ${sigc++-3_INCLUDE_DIRS}
    SYSTEM PRIVATE include/bindings/
  PUBLIC
    include
)


target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ${fmt_LIBRARIES}
    ${imgui_LIBRARIES}
    ${opencv_LIBRARIES}
    ${SFML_LIBRARIES}
    ${sigc++-3_LIBRARIES}
    spdlog::spdlog
)


## Copy resources
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/share DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
