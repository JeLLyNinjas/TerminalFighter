#!/bin/bash -e

astyle *.h *.cpp -r --options=astylerc
find . -name "*.orig" -delete
