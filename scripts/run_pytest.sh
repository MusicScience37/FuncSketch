#!/bin/bash

cd $(dirname $0)/..

if [ "$#" -ge 1 ]; then
    xvfb-run poetry run pytest "$@"
else
    xvfb-run poetry run pytest tests
fi
