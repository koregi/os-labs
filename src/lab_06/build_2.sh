#!/bin/bash

mkdir -p build && pushd build
g++ -o lab_06_2 ../lab_06_2.cpp -lpthread -lrt
./lab_06_2
popd