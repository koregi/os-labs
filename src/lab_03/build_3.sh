#!/bin/bash

mkdir -p build && pushd build
g++ -o lab_03_3 ../lab_03_3.cpp -lpthread
./lab_03_3
popd