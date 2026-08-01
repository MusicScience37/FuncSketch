include(${CMAKE_CURRENT_SOURCE_DIR}/source_list.cmake)
add_executable(func_sketch_test_units ${SOURCE_FILES})
target_add_catch2(func_sketch_test_units)

add_executable(func_sketch_test_units_unity EXCLUDE_FROM_ALL unity_source.cpp)
target_link_libraries(func_sketch_test_units_unity
                      PRIVATE Catch2::Catch2WithMain func_sketch_lib)
