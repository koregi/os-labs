#!/bin/bash

mkdir -p build && pushd build
g++ -o lab_06_1 ../lab_06_1.cpp -lpthread -lrt
./lab_06_1
popd