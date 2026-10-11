add_executable(bench_plotting bench_plotting.cpp)
target_link_libraries(bench_plotting PRIVATE func_sketch_lib
                                             benchmark::benchmark_main)

add_executable(bench_insertion bench_insertion.cpp)
target_link_libraries(bench_insertion PRIVATE func_sketch_lib
                                              benchmark::benchmark_main)
