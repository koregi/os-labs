#!/bin/bash

mkdir -p build && pushd build
g++ -o lab_03_1 ../lab_03_1.cpp -lpthread
./lab_03_1
popd