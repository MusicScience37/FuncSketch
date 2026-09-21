#!/bin/bash -e

# This file is licensed under MIT license as follows:
#
# Copyright 2026 MusicScience37 (Kenta Kabashima)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# usage: collect_llvm_coverage.sh <directory of .profraw files>

# ctest must have been called with LLVM_PROFILE_FILE=<build directory>/coverage/coverage_%p.profraw

ROOT_DIR=$(dirname $0)/..

DIR=$1

ls -lh $DIR/coverage/

# make a file for codecov
llvm-profdata merge -o $DIR/coverage/coverage.profdata $DIR/coverage/coverage_*.profraw
opts=(
    "-ignore-filename-regex=.*/(tests|.venv|.pyenv)/.*"
    "-instr-profile=$DIR/coverage/coverage.profdata"
)
for a in $(find $DIR/bin/func_sketch_test_units $ROOT_DIR/src/func_sketch/_cpp.*.so); do
    opts+=("-object" "$a")
done
llvm-cov show "${opts[@]}" >$DIR/coverage/coverage.txt
llvm-cov show "${opts[@]}" -format=html -output-dir=$DIR/coverage/html

# output in lcov's format
llvm-cov export "${opts[@]}" -format=lcov > $DIR/coverage/coverage

# output summary to stdout
llvm-cov report "${opts[@]}" | tee $DIR/coverage/coverage_summary.txt
