#!/bin/bash

set -e

cd $(dirname $0)

mkdir -p ./build/html
cp ./icon/icon* ./build/html
cp ./version_switcher_config.json ./build/html

./run_doxygen.sh
./generate_plots.py
./update_apidoc.sh
./run_sphinx.sh
