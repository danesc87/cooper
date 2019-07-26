#!/bin/bash

# Some Variables
COMMAND="$1"
THISDIR=$(dirname $(readlink -e ${BASH_SOURCE[0]}))
TEST_DIR="test"
BUILD_DIR="build"
PROJECT_NAME="Cooper"

function check_build_dir {
    if [ ! -d "$BUILD_DIR" ]; then
        mkdir $BUILD_DIR
    fi
}

function cmake_stuff {
    check_build_dir
    cd $BUILD_DIR
    cmake ..
}


if [[ -z $COMMAND ]]; then
    echo "You must specify a command build or test. Exiting..."
    exit 1
fi

if [[ $COMMAND == "build" ]]; then
    echo "Start building sources for $PROJECT_NAME"
    cmake_stuff
    make
fi

if [[ $COMMAND == "build-test" ]]; then
    echo "Start building tests for $PROJECT_NAME"
    cmake_stuff
    cd $TEST_DIR
    make
fi

if [[ $COMMAND == "test" ]]; then
    echo "Start tests for $PROJECT_NAME"
    check_build_dir
    cd $BUILD_DIR
    cd $TEST_DIR
    ctest -j2
fi

if [[ $COMMAND == "clean" ]]; then
    echo "Clean all for $PROJECT_NAME"
    rm -r $BUILD_DIR
fi
