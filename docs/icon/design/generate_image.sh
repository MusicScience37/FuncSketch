#!/bin/bash

set -ex

cd $(dirname $0)
lualatex f.tex < /dev/null
