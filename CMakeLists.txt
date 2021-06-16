cmake_minimum_required(VERSION 3.15)
project(sqlite_cpp VERSION 0.0.1 LANGUAGES CXX)

option(ENABLE_PCH   "Enable Precompiled Headers"  False)
option(ENABLE_TESTS "Enable tests"                False)


## Sources common for all platforms .cpp .hpp
set(SOURCES src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})


## Compiler options
include(cmake/CompilerOptions.cmake)
set_project_options(${PROJECT_NAME})

## Setup Conan
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
      "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_run(CONANFILE conanfile.txt BASIC_SETUP NO_OUTPUT_DIRS)


## Find third-party packages
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_BINARY_DIR})
find_package(fmt REQUIRED)
find_package(SQLite3 REQUIRED)


## Target
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt SQLite::SQLite3)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${PROJECT_NAME} PRIVATE include)


## Check custom options
if (ENABLE_PCH) # Since CMake 3.15
  target_precompile_headers(${PROJECT_NAME} INTERFACE <vector> <string> <map> <utility>)
  message("PCH enabled")
endif ()

if (ENABLE_TESTS)
  message(STATUS "Tests enabled")
  enable_testing() # Must be placed before add_subdirectory
  add_subdirectory(test)
endif ()


## Install commands
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "/opt/${PROJECT_NAME}"
    )

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Juan Jose Castellanos <juancho.312@hotmail.com>")
include(CPack)
