#!/bin/bash

# Usage: create_package.sh <python-version>

set -e

cd $(dirname $0)
cd ..

rm -rf ./dist
rm -rf ./temp

echo "> Create a virtual environment."
mkdir ./temp
cd ./temp
pyenv local $1
pyenv exec python3 -m venv .venv
source .venv/bin/activate
cd ..

echo "> Created a virtual environment with:"
python --version

echo "> Create a wheel."
pip3 install -U pip
pip3 install build
python3 -m build -w

echo "> Test the wheel."
pip3 install ./dist/*.whl
xvfb-run func_sketch --help

echo "> Completed!"
