#!/bin/bash

set -e

cd $(dirname $0)
./run_doxygen.sh
./update_apidoc.sh
./run_sphinx.sh
