#!/bin/sh

basedir=$(pwd -L)
# Use "pwd -P" for the path without links. man bash for more info.

export ROS_MASTER_URI='http://192.168.1.123:11311/'
export ROS_HOSTNAME=192.168.1.239
export ROS_IP=192.168.1.239

