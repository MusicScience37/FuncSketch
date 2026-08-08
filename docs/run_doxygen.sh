#!/bin/bash

set -e

cd $(dirname $0)/..

mkdir -p ./docs/build/html/doxygen
doxygen ./docs/doxygen/Doxyfile
