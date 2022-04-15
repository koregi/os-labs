#!/bin/bash

mkdir -p build && pushd build
g++ -o lab_03_2 ../lab_03_2.cpp -lpthread
./lab_03_2
popd