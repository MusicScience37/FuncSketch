#!/bin/bash

set -e

cd $(dirname $0)
./run_doxygen.sh
./generate_plots.py
./update_apidoc.sh
KIVY_NO_ARGS=1 \
    SPHINX_AUTODOC_IGNORE_NATIVE_MODULE_TYPE_STUBS=1 \
    sphinx-autobuild \
    sphinx build/html \
    -D plantuml="java -jar ${PLANTUML_JAR_PATH}" \
    -d build/doctrees \
    --port 4762
