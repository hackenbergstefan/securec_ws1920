#!/usr/bin/env sh
jupyter nbconvert --execute --to html_toc --debug --ExecutePreprocessor.timeout=180 $1
