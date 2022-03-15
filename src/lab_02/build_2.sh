#!/bin/bash

mkdir -p build && pushd build
g++ -o lab_02_2 ../lab_02_2.cpp -lpthread
./lab_02_2
popd
