#!/bin/bash

# Usage: create_wheel_on_many_linux.sh <python_version>

set -e

cd $(dirname $0)
cd ..

PYTHON_VERSION="$1"
PYTHON_BIN_DIR="/opt/python/${PYTHON_VERSION}/bin"

rm -rf ./dist
rm -rf ./temp
echo "> Create a virtual environment."
mkdir ./temp
cd ./temp
${PYTHON_BIN_DIR}/python -m venv .venv
source .venv/bin/activate
cd ..

echo "> Created a virtual environment with:"
python --version

echo "> Create a wheel."
pip install -U pip
pip install build
python3 -m build -w

echo "> Repair the wheel for manylinux."
auditwheel show ./dist/*.whl
auditwheel repair ./dist/*.whl -w ./dist_manylinux/

echo "> Test the wheel."
pip3 install ./dist_manylinux/*.whl
func_sketch --help

echo "> Completed!"
