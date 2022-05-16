#!/bin/bash

mkdir -p build && pushd build
g++ -o lab_05_1 ../lab_05_1.cpp -pthread
./lab_05_1
popd