#!/bin/bash

set -e

cd $(dirname $0)
KIVY_NO_ARGS=1 \
    SPHINX_AUTODOC_IGNORE_NATIVE_MODULE_TYPE_STUBS=1 \
    sphinx-build \
    -b html \
    sphinx build/html \
    -D plantuml="java -jar ${PLANTUML_JAR_PATH}" \
    -d build/doctrees \
    -W -q
