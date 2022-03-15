#!/bin/bash

mkdir build -p
cd build
g++ -c ../lab_02_3.cpp
g++ -o lab_02_3 lab_02_3.o -pthread
./lab_02_3
