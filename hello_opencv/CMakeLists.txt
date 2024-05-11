cmake_minimum_required(VERSION 3.28)

project(hello_opencv
  VERSION "1.0.0"
  DESCRIPTION "Hello OpenCV with conan"
  LANGUAGES CXX
)

# Options
option(ENABLE_WERROR   "Treat compiler warnings as errors" False)


# GLOB source files
file(GLOB_RECURSE
  SOURCE_FILES
  src/*.cpp
  src/main.cpp
)

## Set the project as an executable target
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

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
find_package(fmt REQUIRED)
find_package(OpenCV REQUIRED)


## Target
target_include_directories(${PROJECT_NAME}
  SYSTEM PRIVATE
    ${opencv_INCLUDES}
    ${fmt_INCLUDES}
  PUBLIC
    include
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ${fmt_LIBRARIES}
    ${opencv_LIBRARIES}
)


## Copy resources
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/share DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
