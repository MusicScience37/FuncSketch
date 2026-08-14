#!/bin/bash

set -ex

cd $(dirname $0)
latex f.tex < /dev/null
dvipdfmx -o f.pdf f.dvi
