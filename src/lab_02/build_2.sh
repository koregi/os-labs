#!/bin/bash

mkdir build -p
cd build
g++ -c ../lab_02_2.cpp
g++ -o lab_02_2 lab_02_2.o -pthread
./lab_02_2
