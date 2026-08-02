include(${CMAKE_CURRENT_SOURCE_DIR}/source_list.cmake)
add_library(func_sketch_lib STATIC ${SOURCE_FILES})
target_include_directories(func_sketch_lib
                           PUBLIC ${FUNC_SKETCH_CPP_INCLUDE_DIR})
target_link_libraries(func_sketch_lib PUBLIC Boost::spirit Boost::math
                                             Eigen3::Eigen OpenCV fmt::fmt)
target_compile_features(func_sketch_lib PUBLIC cxx_std_23)
set_target_properties(func_sketch_lib PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Unity build target used for clang-tidy checks.
add_library(func_sketch_lib_unity EXCLUDE_FROM_ALL STATIC unity_source.cpp)
target_include_directories(func_sketch_lib_unity
                           PUBLIC ${FUNC_SKETCH_CPP_INCLUDE_DIR})
target_link_libraries(
    func_sketch_lib_unity PUBLIC Boost::spirit Boost::math Eigen3::Eigen OpenCV
                                 fmt::fmt)
target_compile_features(func_sketch_lib_unity PUBLIC cxx_std_23)

# Workaround errors in MSVC.
if(MSVC)
    target_compile_options(func_sketch_lib PUBLIC /bigobj /EHsc /utf-8)
endif()
