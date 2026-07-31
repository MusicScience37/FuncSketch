#!/bin/bash

set -e

cd $(dirname $0)
sphinx-autobuild \
    sphinx build \
    --port 4762
