#!/bin/bash

set -e

cd $(dirname $0)
sphinx-autobuild \
    sphinx build \
    -D plantuml="java -jar ${PLANTUML_JAR_PATH}" \
    --port 4762
