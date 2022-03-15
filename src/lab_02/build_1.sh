#!/bin/bash

mkdir -p build && pushd build
g++ -o lab_02_1 ../lab_02_1.cpp -lpthread
./lab_02_1
popd
