cmake_minimum_required(VERSION 3.15)
project(func_sketch LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cpp/cmake")

# ##############################################################################
# Configuration of CTest
# ##############################################################################
set(BUILDNAME
    "${CMAKE_HOST_SYSTEM_NAME}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}-${CMAKE_BUILD_TYPE}"
)
include(CTest)

# ##############################################################################
# Options
# ##############################################################################
option(FUNC_SKETCH_BUILD_TESTS "Build tests" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS
    ON
    CACHE BOOL "export compile commands" FORCE)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ##############################################################################
# Directory of binaries
# ##############################################################################
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/lib>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/lib>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/bin>)

# ##############################################################################
# Dependencies
# ##############################################################################
find_package(Boost REQUIRED COMPONENTS spirit math)

find_package(Eigen3 CONFIG REQUIRED)

set(OpenCV_ROOT "${VCPKG_INSTALLED_DIR}/x64-linux/share/opencv4")
find_package(OpenCV REQUIRED)
add_library(OpenCV INTERFACE)
target_include_directories(OpenCV INTERFACE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(OpenCV INTERFACE ${OpenCV_LIBS})

find_package(fmt CONFIG REQUIRED)

find_package(Catch2 CONFIG REQUIRED)

find_path(APPROVAL_TESTS_CPP_INCLUDE_DIRS "ApprovalTests.hpp")
add_library(ApprovalTestsCpp INTERFACE)
target_include_directories(ApprovalTestsCpp
                           INTERFACE ${APPROVAL_TESTS_CPP_INCLUDE_DIRS})

# ##############################################################################
# Import modules for configurations
# ##############################################################################
include(ConfigureCcache)
include(ConfigureSanitizer)

# ##############################################################################
# Build targets
# ##############################################################################
add_subdirectory(cpp)
