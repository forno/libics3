cmake_minimum_required(VERSION 2.8.12)
project(ics3 CXX)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Winit-self -Wno-missing-field-initializers -g -fPIC")
set(CMAKE_INSTALL_PREFIX /usr/local)

################################################################
set(ICS3_MAJOR_VERSION 0)
set(ICS3_MINOR_VERSION 1)
set(ICS3_PATCH_VERSION 0)

set(ICS3_VERSION
  ${ICS3_MAJOR_VERSION}.${ICS3_MINOR_VERSION}.${ICS3_PATCH_VERSION}
)

################################################################
set(ICS3_SOURCES
  ${PROJECT_SOURCE_DIR}/src/angle.cpp
  ${PROJECT_SOURCE_DIR}/src/core.cpp
  ${PROJECT_SOURCE_DIR}/src/eepparam.cpp
  ${PROJECT_SOURCE_DIR}/src/eeprom.cpp
  ${PROJECT_SOURCE_DIR}/src/ics3.cpp
  ${PROJECT_SOURCE_DIR}/src/id.cpp
  ${PROJECT_SOURCE_DIR}/src/parameter.cpp
)

set(ICS3_HEADER_DIR
  ${PROJECT_SOURCE_DIR}/include
)

################################################################
include_directories(
  ${PROJECT_HEADER_DIR}
)

link_directories(
)

add_library(ics3
  SHARED ${ICS3_SOURCES}
)

target_link_libraries(ics3)

################################################################
set_target_properties(ics3 PROPERTIES
  VERSION    ${ICS3_VERSION}
  SOVERSION  ${ICS3_MAJOR_VERSION}
)

install(TARGETS ics3
  LIBRARY DESTINATION lib
)

install(DIRECTORY
  ${ICS3_HEADER_DIR}/ics3 DESTINATION include
)
