#!/bin/bash

set -e

cd $(dirname $0)
./run_doxygen.sh
./generate_plots.py
./update_apidoc.sh
sphinx-autobuild \
    SPHINX_AUTODOC_IGNORE_NATIVE_MODULE_TYPE_STUBS=1 \
    sphinx build/html \
    -D plantuml="java -jar ${PLANTUML_JAR_PATH}" \
    -d build/doctrees \
    --port 4762
