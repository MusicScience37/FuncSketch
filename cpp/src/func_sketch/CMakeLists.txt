include(${CMAKE_CURRENT_SOURCE_DIR}/source_list.cmake)
add_library(func_sketch_lib STATIC ${SOURCE_FILES})
target_include_directories(func_sketch_lib
                           PUBLIC ${FUNC_SKETCH_CPP_INCLUDE_DIR})
target_link_libraries(func_sketch_lib PUBLIC Boost::spirit Boost::math OpenCV
                                             fmt::fmt)
target_compile_features(func_sketch_lib PUBLIC cxx_std_23)
set_target_properties(func_sketch_lib PROPERTIES POSITION_INDEPENDENT_CODE ON)

set(FUNC_SKETCH_GENERATED_HEADER_DIR "${CMAKE_BINARY_DIR}/generated/include")
file(MAKE_DIRECTORY "${FUNC_SKETCH_GENERATED_HEADER_DIR}/func_sketch")
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/version.h.in"
    "${FUNC_SKETCH_GENERATED_HEADER_DIR}/func_sketch/version.h" @ONLY)
target_include_directories(
    func_sketch_lib
    PUBLIC $<BUILD_INTERFACE:${FUNC_SKETCH_GENERATED_HEADER_DIR}>)

# Workaround errors in MSVC.
if(MSVC)
    target_compile_options(func_sketch_lib PUBLIC /bigobj /EHsc /utf-8)
endif()
