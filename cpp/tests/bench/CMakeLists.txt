add_executable(bench_plotting bench_plotting.cpp)
target_link_libraries(bench_plotting PRIVATE func_sketch_lib
                                             benchmark::benchmark_main)
