cmake_minimum_required(VERSION 2.8.12.1)
project(ics3 C CXX)

set(PROJECT_VER_MAJOR 1)
set(PROJECT_VER_MINOR 5)
set(PROJECT_VER_PATCH 0)
set(PROJECT_VER "${PROJECT_VER_MAJOR}.${PROJECT_VER_MINOR}.${PROJECT_VER_PATCH}")
set(PROJECT_APIVER "${PROJECT_VER_MAJOR}.${PROJECT_VER_MINOR}")

if(NOT DEFINED CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose: RelWithDebInfo Release Debug MinSizeRel None")
endif()

option(BUILD_SHARED_LIBS "Build shared (ON) or static (OFF) libraries" OFF)
option(ENABLE_TEST "Enable test program building" OFF)

set(MY_DIR ${ics3_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

#set the default path for built executables to the "bin" directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

#set the default path for built libraries to the "lib" directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# Add includes
include_directories(
  ${MY_DIR}/include
)

file(GLOB ICS3_SOURCES
  ${MY_DIR}/src/*.cpp
)

file(GLOB ICS3_HEADERS
  ${MY_DIR}/include/ics3/*.hpp
  ${MY_DIR}/include/core.hpp
)

set(SOURCES
  ${ICS3_HEADERS}
  ${ICS3_SOURCES}
)

add_library(ics3 ${SOURCES})
set_target_properties(ics3 PROPERTIES
  VERSION ${PROJECT_VER}
  SOVERSION ${PROJECT_APIVER}
)

target_link_libraries(ics3)

if(ENABLE_TEST)
  set(GTEST_ROOT ${MY_DIR}/thirdpatry/googletest/googletest)
  find_package(GTest REQUIRED)
  find_package(Threads)

  include_directories(${GTEST_INCLUDE_DIRS})
  add_executable(angle test/angle.cpp)
  add_executable(baudrate test/baudrate.cpp)
  add_executable(eepparam test/eepparam.cpp)
  add_executable(id test/id.cpp)
  add_executable(parameter test/parameter.cpp)
  add_executable(ics3Test test/ics3.cpp)
  target_link_libraries(angle ics3 ${GTEST_BOTH_LIBRARIES})
  target_link_libraries(baudrate ics3 ${GTEST_BOTH_LIBRARIES})
  target_link_libraries(eepparam ics3 ${GTEST_BOTH_LIBRARIES})
  target_link_libraries(id ics3 ${GTEST_BOTH_LIBRARIES})
  target_link_libraries(parameter ics3 ${GTEST_BOTH_LIBRARIES})
  target_link_libraries(ics3Test ics3 ${GTEST_BOTH_LIBRARIES})
  if(THREADS_HAVE_PTHREAD_ARG)
    target_compile_options(PUBLIC angle "-pthread")
    target_compile_options(PUBLIC baudrate "-pthread")
    target_compile_options(PUBLIC eepparam "-pthread")
    target_compile_options(PUBLIC id "-pthread")
    target_compile_options(PUBLIC parameter "-pthread")
    target_compile_options(PUBLIC ics3Test "-pthread")
  endif()
  if(CMAKE_THREAD_LIBS_INIT)
    target_link_libraries(angle "${CMAKE_THREAD_LIBS_INIT}")
    target_link_libraries(baudrate "${CMAKE_THREAD_LIBS_INIT}")
    target_link_libraries(eepparam "${CMAKE_THREAD_LIBS_INIT}")
    target_link_libraries(id "${CMAKE_THREAD_LIBS_INIT}")
    target_link_libraries(parameter "${CMAKE_THREAD_LIBS_INIT}")
    target_link_libraries(ics3Test "${CMAKE_THREAD_LIBS_INIT}")
  endif()

  enable_testing()
  add_test(AngleTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/angle)
  add_test(BaudrateTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/baudrate)
  add_test(EepParamTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/eepparam)
  add_test(IDTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/id)
  add_test(ParameterTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/parameter)
  add_test(ICS3Test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ics3Test)
endif()

install(TARGETS ics3 DESTINATION lib RUNTIME DESTINATION bin)
install(DIRECTORY "${MY_DIR}/include/${PROJECT_NAME}" DESTINATION include)

get_cmake_property(vars VARIABLES)
message(STATUS "Feature list:")
foreach(var ${vars})
  if(var MATCHES ^HAVE_)
    string(REPLACE HAVE_ "" feature ${var})
    message(STATUS "  ${feature}    ${${var}}")
  endif()
endforeach()
