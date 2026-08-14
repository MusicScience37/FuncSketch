#!/bin/bash

set -e

cd $(dirname $0)/..
./scripts/run_pytest.sh bench --benchmark-autosave
