cmake_minimum_required(VERSION 3.15)
project(FuncSketch LANGUAGES CXX)

# ##############################################################################
# Options
# ##############################################################################
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

# ##############################################################################
# Build targets
# ##############################################################################
add_subdirectory(cpp)
