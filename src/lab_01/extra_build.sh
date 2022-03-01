#!/bin/bash

mkdir build -p && pushd build
g++ -o extra_task_01 ../extra_task_01.cpp -pthread
./extra_task_01
popd
