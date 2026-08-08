#!/bin/bash -e

# usage: collect_llvm_coverage.sh <directory of .profraw files>

# ctest must have been called with LLVM_PROFILE_FILE=<build directory>/coverage/coverage_%p.profraw

ROOT_DIR=$(dirname $0)/..

DIR=$1

ls -lh $DIR/coverage/

# make a file for codecov
llvm-profdata merge -o $DIR/coverage/coverage.profdata $DIR/coverage/coverage_*.profraw
opts="-ignore-filename-regex='.*/(tests|.venv|.pyenv)/.*' -instr-profile=$DIR/coverage/coverage.profdata"
for a in $(find $DIR/bin/func_sketch_test_units $ROOT_DIR/src/func_sketch/_cpp.*.so); do
    opts="$opts -object $a"
done
llvm-cov show $opts >$DIR/coverage/coverage.txt
llvm-cov show $opts -format=html -output-dir=$DIR/coverage/html

# output in lcov's format
llvm-cov export $opts -format=lcov > $DIR/coverage/coverage

# output summary to stdout
llvm-cov report $opts | tee $DIR/coverage/coverage_summary.txt
