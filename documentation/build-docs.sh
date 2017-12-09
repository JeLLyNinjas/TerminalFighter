#!/bin/bash

# "doxygen -g" will create a default config file named Doxyfile
# "patch < Doxyfile.patch" will apply the configuration patch

doxygen -g
patch --no-backup-if-mismatch < ./documentation/Doxyfile.patch 
doxygen Doxyfile 
chown 1000:1000 -R .
rm Doxyfile
