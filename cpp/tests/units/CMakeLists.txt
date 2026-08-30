include(${CMAKE_CURRENT_SOURCE_DIR}/source_list.cmake)
add_executable(func_sketch_test_units ${SOURCE_FILES})
target_add_catch2(func_sketch_test_units)
target_add_ausan(func_sketch_test_units)
