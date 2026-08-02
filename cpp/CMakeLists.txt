set(FUNC_SKETCH_CPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(src)
if(FUNC_SKETCH_BUILD_TESTS)
    add_subdirectory(tests)
endif()
