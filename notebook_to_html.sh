#!/usr/bin/env sh
NOTEBOOK_PATH="$1" jupyter nbconvert --execute --to html_toc --debug --ExecutePreprocessor.timeout=1800 $1
