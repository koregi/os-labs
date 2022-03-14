#!/bin/bash

mkdir build -p
cd build
g++ -c ../lab_02_1.cpp
g++ -o lab_02_1 lab_02_1.o -pthread
./lab_02_1
