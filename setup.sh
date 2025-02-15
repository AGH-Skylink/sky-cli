#!/bin/bash

install_lib() {
    cmake -S . -B build/
    cmake --build build/
    cmake --install build/
}

case $1 in
    install)
        install_lib
        exit 0;
        ;;
    uninstall)
        xargs rm -rf < build/install_manifest.txt
        rmdir /usr/local/include/skycli
        exit 0;
        ;;
    *)
        if [ -z "$1" ]
        then
            install_lib
            exit 0
        fi
        echo "Error: Unrecognized command."
        exit 0
        ;;
esac