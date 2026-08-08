#!/bin/bash

set -e

cd $(dirname $0)
./run_doxygen.sh
./update_apidoc.sh
sphinx-autobuild \
    sphinx build/html \
    -D plantuml="java -jar ${PLANTUML_JAR_PATH}" \
    -d build/doctrees \
    --port 4762
