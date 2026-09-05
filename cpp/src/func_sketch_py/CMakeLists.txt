nanobind_add_module(_cpp STABLE_ABI func_sketch_module.cpp)
target_link_libraries(_cpp PUBLIC func_sketch_lib)
# Workaround for warnings of nanobind.
target_compile_options(_cpp PRIVATE -Wno-macro-redefined)

if(SKBUILD)
    set_target_properties(
        _cpp PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

    install(TARGETS _cpp LIBRARY DESTINATION func_sketch)

    nanobind_add_stub(
        func_sketch_py_stub
        MODULE
        _cpp
        OUTPUT
        ${CMAKE_CURRENT_BINARY_DIR}/_cpp.pyi
        PYTHON_PATH
        ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS
        _cpp)

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/_cpp.pyi DESTINATION func_sketch)
else()
    set_target_properties(
        _cpp
        PROPERTIES LIBRARY_OUTPUT_DIRECTORY
                   ${FUNC_SKETCH_ROOT_DIR}/src/func_sketch
                   RUNTIME_OUTPUT_DIRECTORY
                   ${FUNC_SKETCH_ROOT_DIR}/src/func_sketch)

    nanobind_add_stub(
        func_sketch_py_stub
        MODULE
        func_sketch._cpp
        OUTPUT
        ${FUNC_SKETCH_ROOT_DIR}/src/func_sketch/_cpp.pyi
        PYTHON_PATH
        ${FUNC_SKETCH_ROOT_DIR}/src
        DEPENDS
        _cpp)
endif()
