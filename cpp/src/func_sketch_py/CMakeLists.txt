nanobind_add_module(_cpp func_sketch_module.cpp)
target_link_libraries(_cpp PUBLIC func_sketch_lib)
set_target_properties(
    _cpp
    PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${FUNC_SKETCH_ROOT_DIR}/src/func_sketch
               RUNTIME_OUTPUT_DIRECTORY ${FUNC_SKETCH_ROOT_DIR}/src/func_sketch)
# Workaround for warnings of nanobind.
target_compile_options(_cpp PRIVATE -Wno-macro-redefined)
