#!/bin/bash

mkdir -p build && pushd build
g++ -o lab_02_3 ../lab_02_3.cpp -lpthread
./lab_02_3
popd
