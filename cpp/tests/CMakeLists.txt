option(FUNC_SKETCH_WRITE_JUNIT "write JUnit XML files in tests" OFF)
set(FUNC_SKETCH_JUNIT_DIR
    "${CMAKE_BINARY_DIR}/junit"
    CACHE PATH "directory to which JUnit XML files are written" FORCE)
if(FUNC_SKETCH_WRITE_JUNIT)
    file(MAKE_DIRECTORY ${FUNC_SKETCH_JUNIT_DIR})
endif()

set(FUNC_SKETCH_TEMP_TEST_DIR
    "${CMAKE_BINARY_DIR}/temp_test"
    CACHE PATH "directory used in test" FORCE)
file(MAKE_DIRECTORY ${FUNC_SKETCH_TEMP_TEST_DIR})

add_library(func_sketch_test_util INTERFACE)
target_include_directories(func_sketch_test_util
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/util/include)

macro(target_add_catch2 TARGET)
    target_link_libraries(
        ${TARGET} PRIVATE Catch2::Catch2WithMain ApprovalTestsCpp
                          func_sketch_test_util func_sketch_lib)

    if(FUNC_SKETCH_WRITE_JUNIT)
        set(CATCH2_REPORT_OPTIONS -r junit -o
                                  ${FUNC_SKETCH_JUNIT_DIR}/${TARGET}.xml)
    else()
        set(CATCH2_REPORT_OPTIONS -r console)
    endif()

    add_test(
        NAME ${TARGET}
        COMMAND ${TARGET} ${CATCH2_REPORT_OPTIONS}
        WORKING_DIRECTORY ${FUNC_SKETCH_TEMP_TEST_DIR})
endmacro()

add_subdirectory(units)
