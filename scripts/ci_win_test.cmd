@REM This file is licensed under MIT license as follows:
@REM
@REM Copyright 2026 MusicScience37 (Kenta Kabashima)
@REM
@REM Permission is hereby granted, free of charge, to any person obtaining a copy
@REM of this software and associated documentation files (the "Software"), to deal
@REM in the Software without restriction, including without limitation the rights
@REM to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
@REM copies of the Software, and to permit persons to whom the Software is
@REM furnished to do so, subject to the following conditions:
@REM
@REM The above copyright notice and this permission notice shall be included in all
@REM copies or substantial portions of the Software.
@REM
@REM THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
@REM IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
@REM FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
@REM AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
@REM LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
@REM OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
@REM SOFTWARE.

@REM Enable delayed expansion to propagate exit codes using !ERRORLEVEL!.
setlocal EnableDelayedExpansion

@REM Below is used in my runner.
call "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat" x86_x64 || exit /b !ERRORLEVEL!

@REM Use a short path for build trees of vcpkg to avoid errors due to long paths.
for %%I in ("%CD%\..\.vb") do set VCPKG_BUILDTREES_ROOT=%%~fI
set VCPKG_INSTALL_OPTIONS=--x-buildtrees-root=%VCPKG_BUILDTREES_ROOT%
set SKBUILD_CMAKE_ARGS=-DVCPKG_INSTALL_OPTIONS=%VCPKG_INSTALL_OPTIONS%

cmake .. ^
    -G Ninja ^
    -DCMAKE_BUILD_TYPE=Release ^
    -DVCPKG_TARGET_TRIPLET:STRING=x64-windows-static-md ^
    -DVCPKG_INSTALL_OPTIONS:STRING=%VCPKG_INSTALL_OPTIONS% ^
    -DFUNC_SKETCH_BUILD_TESTS:BOOL=ON ^
    -DFUNC_SKETCH_ENABLE_CCACHE:BOOL=ON ^
    -DFUNC_SKETCH_ENABLE_AUSAN:BOOL=OFF ^
    -DFUNC_SKETCH_WRITE_JUNIT:BOOL=ON || exit /b !ERRORLEVEL!

cmake --build . --config Release --parallel || exit /b !ERRORLEVEL!

ctest -V --build-config Release || exit /b !ERRORLEVEL!

cd .. || exit /b !ERRORLEVEL!

poetry run pytest tests -v || exit /b !ERRORLEVEL!
poetry run pytest system_tests -v || exit /b !ERRORLEVEL!
poetry run pytest bench -v --benchmark-json=benchmark.json || exit /b !ERRORLEVEL!
poetry run python scripts/generate_benchmark_metrics.py benchmark.json bench_metrics.txt || exit /b !ERRORLEVEL!

python -m cibuildwheel --output-dir dist_win --platform windows --archs native || exit /b !ERRORLEVEL!
