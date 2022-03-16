#!/bin/bash

mkdir -p build && pushd build
g++ -o extra_task_02 ../extra_task_02.cpp -lpthread
./extra_task_02
popd
