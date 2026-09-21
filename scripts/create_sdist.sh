#!/bin/bash

# This file is licensed under MIT license as follows:
#
# Copyright 2026 MusicScience37 (Kenta Kabashima)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# Usage: create_sdist.sh <python_version>

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

echo "> Create a source distribution."
pip3 install -U pip
pip3 install build
python3 -m build -s

echo "> Test the source distribution."
pip3 install ./dist/*.tar.gz
xvfb-run func_sketch --help

echo "> Completed!"
