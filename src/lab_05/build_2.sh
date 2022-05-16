#!/bin/bash

mkdir -p build && pushd build
g++ -o lab_05_2 ../lab_05_2.cpp -pthread
./lab_05_2
popd