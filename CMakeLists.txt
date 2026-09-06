cmake_minimum_required(VERSION 3.19)

# ##############################################################################
# Configuration of vcpkg
# ##############################################################################
if(DEFINED ENV{VCPKG_ROOT})
    set(VCPKG_ROOT $ENV{VCPKG_ROOT})
else()
    set(VCPKG_CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg-configuration.json)
    file(READ ${VCPKG_CONFIG_FILE} VCPKG_CONFIG_CONTENT)
    string(JSON VCPKG_BASELINE GET ${VCPKG_CONFIG_CONTENT} "default-registry"
           "baseline")

    include(FetchContent)
    fetchcontent_declare(
        vcpkg
        GIT_REPOSITORY "https://github.com/Microsoft/vcpkg"
        GIT_TAG "${VCPKG_BASELINE}")
    fetchcontent_makeavailable(vcpkg)
    set(VCPKG_ROOT ${vcpkg_SOURCE_DIR})
endif()
set(CMAKE_TOOLCHAIN_FILE
    "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "" FORCE)

# ##############################################################################
# Options
# ##############################################################################
option(FUNC_SKETCH_BUILD_TESTS "Build tests" OFF)
if(FUNC_SKETCH_BUILD_TESTS)
    list(APPEND VCPKG_MANIFEST_FEATURES "tests")
endif()

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
# Settings of CMake
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

# Find nanobind installed via poetry.
find_program(POETRY_EXECUTABLE NAMES poetry)
if(POETRY_EXECUTABLE)
    execute_process(
        COMMAND "${POETRY_EXECUTABLE}" "env" "info" "--path"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE POETRY_VENV_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE)
    message(STATUS "Virtualenv location: ${POETRY_VENV_DIR}")

    find_program(
        Python_EXECUTABLE
        NAMES python3 python
        PATHS ${POETRY_VENV_DIR}/bin ${POETRY_VENV_DIR}/Scripts
        NO_DEFAULT_PATH)
endif()
find_package(
    Python
    COMPONENTS Interpreter Development.Module Development.SABIModule
    REQUIRED)
execute_process(
    COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
    OUTPUT_STRIP_TRAILING_WHITESPACE
    OUTPUT_VARIABLE nanobind_ROOT)
find_package(nanobind CONFIG REQUIRED)

if(FUNC_SKETCH_BUILD_TESTS)
    find_package(Catch2 CONFIG REQUIRED)

    find_path(APPROVAL_TESTS_CPP_INCLUDE_DIRS "ApprovalTests.hpp")
    add_library(ApprovalTestsCpp INTERFACE)
    target_include_directories(ApprovalTestsCpp
                               INTERFACE ${APPROVAL_TESTS_CPP_INCLUDE_DIRS})

    find_package(benchmark CONFIG REQUIRED)
endif()

# ##############################################################################
# Import modules for configurations
# ##############################################################################
include(ConfigureCcache)
include(ConfigureSanitizer)

# ##############################################################################
# Build targets
# ##############################################################################
set(FUNC_SKETCH_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(cpp)
