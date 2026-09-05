#!/bin/bash

set -e

cd $(dirname $0)

rm -rf ./sphinx/python_api
poetry run sphinx-apidoc -H "Python API Reference" -f -e -q -P -d 2 -o ./sphinx/python_api ../src/func_sketch
