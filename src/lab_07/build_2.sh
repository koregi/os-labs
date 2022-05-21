#!/bin/bash

mkdir -p build && pushd build
g++ -o lab_07_2 ../lab_07_2.cpp -lpthread -lrt
./lab_07_2
popd