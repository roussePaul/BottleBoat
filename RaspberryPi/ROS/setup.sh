#!/bin/sh

basedir=$(pwd -L)
# Use "pwd -P" for the path without links. man bash for more info.

export QUICK2WIRE_API_HOME=$basedir/src/compass/include/compass/quick2wire-python-api
export PYTHONPATH=$PYTHONPATH:$QUICK2WIRE_API_HOME
