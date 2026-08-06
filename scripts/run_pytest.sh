#!/bin/bash

cd $(dirname $0)/..

xvfb-run poetry run pytest tests
