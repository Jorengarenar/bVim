cmake_minimum_required(VERSION 3.10)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/extern/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(PreventInSourceBuilds)

project(SHE
  VERSION 0.0.1
  DESCRIPTION "Simple Hex Editor"
  HOMEPAGE_URL "https://joren.ga/she"
  LANGUAGES CXX)

string(TOLOWER "${CMAKE_PROJECT_NAME}" EXECUTABLE_NAME)

add_definitions(-DPROJECT_NAME="${CMAKE_PROJECT_NAME}")
add_definitions(-DVERSION="${CMAKE_PROJECT_VERSION}")
add_definitions(-DEXECUTABLE_NAME="${EXECUTABLE_NAME}")

include(DefineOutputDirs)
include(ExportCompileCommands)

include(ExternalProject)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -pedantic")

set(ONLY_DOCS NO CACHE BOOL "Whether to build only docs")

set(DEPS_DIR ${CMAKE_BINARY_DIR}/extern) # where to install dependencies

if(NOT ONLY_DOCS)

  find_package(Curses REQUIRED)

  find_library(JCBCPP JCBC++)
  if(NOT JCBCPP)
    ExternalProject_Add(libJCBC++
      PREFIX ""
      SOURCE_DIR ${CMAKE_SOURCE_DIR}
      SOURCE_SUBDIR "extern/libJCBC++"
      INSTALL_DIR "${DEPS_DIR}"
      CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
      )

    set(JCBCPP "JCBC++")
    add_library(${JCBCPP} STATIC IMPORTED)
    set_target_properties(${JCBCPP} PROPERTIES IMPORTED_LOCATION ${DEPS_DIR}/lib/libJCBC++.a)
    include_directories(${DEPS_DIR}/include/)
  endif()

  include_directories(include/)

  add_subdirectory(src/)

  include(AddExecutable)

  include(CTest)
  add_subdirectory(tests/)

  install(TARGETS "${CMAKE_PROJECT_NAME}")
endif()

add_subdirectory(docs/)
