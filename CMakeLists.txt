cmake_minimum_required(VERSION 3.13)
project(sqlite_cpp VERSION 0.0.1 LANGUAGES CXX)

#set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} src/main.cpp)

# Options
option(ENABLE_PCH         "Enable Precompiled Headers" FALSE)
option(ENABLE_TESTS       "Enable tests" FALSE)
option(ENABLE_CONAN       "Enable Conan" FALSE)
option(ENABLE_WARN_AS_ERR "Treat compiler warnings as errors" FALSE)
option(ENABLE_COVERAGE    "Enable gcov coverage" FALSE)

# Standard compiler warnings
set(GCC_OPTIONS
    #    -O3
    -Wall
    )

if(ENABLE_WARN_AS_ERR)
  set(GCC_OPTIONS ${GCC_OPTIONS} -Werror)
endif()

# Compiler
if(MSVC)
  set(PROJECT_OPTIONS ${MSVC_WARNINGS})
elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  set(PROJECT_OPTIONS ${CLANG_WARNINGS})
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(PROJECT_OPTIONS ${GCC_OPTIONS})
  if(ENABLE_COVERAGE)
    message("Using gcov")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
  endif()
else()
  message(AUTHOR_WARNING "No compiler warnings set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
endif()

# Sources
set(SOURCES
#    src/URIHandler.cpp
    )

# ---
# target instructions must be set after add_executable or add_library instructions
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_compile_options(${PROJECT_NAME} INTERFACE ${PROJECT_OPTIONS})

# Get the sources
target_sources(${PROJECT_NAME} PUBLIC ${SOURCES} src/main.cpp)

# Get the headers
#set(INCLUDES include)
#include_directories(PUBLIC ${INCLUDES})
#target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})

# Custom Options
if(ENABLE_PCH)
  # Since CMake 3.15
  set(PC_HEADERS <vector> <string>)
  if (ENABLE_CONAN)
#    set(PC_HEADERS ${PC_HEADERS} <gtest/gtest.h>)
  endif()

  target_precompile_headers(${PROJECT_NAME} INTERFACE ${PC_HEADERS})
  message("Pre compiled headers enabled")
endif()

if (ENABLE_CONAN)
  message("-- Conan enabled")
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup()
  target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
  message("-- Conan libs: ${CONAN_LIBS}")
#  conan_target_link_libraries(${TEST_NAME} CONAN_PKG::gtest )
endif ()


if(ENABLE_TESTS)
  enable_testing()
#  add_subdirectory(test)
elseif()
  message("Tests not included")
endif()
