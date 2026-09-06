@REM Below is used in my runner.
call "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat" x86_x64

cmake .. ^
    -G Ninja ^
    -DCMAKE_BUILD_TYPE=Release ^
    -DFUNC_SKETCH_BUILD_TESTS:BOOL=ON ^
    -DFUNC_SKETCH_ENABLE_CCACHE:BOOL=ON ^
    -DFUNC_SKETCH_ENABLE_AUSAN:BOOL=OFF ^
    -DFUNC_SKETCH_WRITE_JUNIT:BOOL=ON

cmake --build . --config Release --parallel

ctest -V --build-config Release

cd ..

poetry run pytest tests -v
poetry run pytest bench -v --benchmark-json=benchmark.json
poetry run python scripts/generate_benchmark_metrics.py benchmark.json bench_metrics.txt

python -m cibuildwheel --output-dir dist_win --platform windows --archs native
