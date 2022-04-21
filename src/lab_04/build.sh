#!/bin/bash

mkdir -p build && pushd build
g++ -o lab_04_1 ../lab_04_1.cpp
g++ -o lab_04_2 ../lab_04_2.cpp
./lab_04_2
popd