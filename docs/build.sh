#!/bin/bash

set -e

cd $(dirname $0)
./run_doxygen.sh
./generate_plots.py
./update_apidoc.sh
./run_sphinx.sh
