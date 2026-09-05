add_executable(profile_plotting profile_plotting.cpp)
target_link_libraries(profile_plotting PRIVATE func_sketch_lib
                                               gperftools::libprofiler)
