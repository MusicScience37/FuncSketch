#!/bin/bash

set -e

cd $(dirname $0)/..

doxygen ./docs/doxygen/Doxyfile
