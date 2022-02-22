#!/bin/bash

mkdir build -p
cd build
g++ -c ../lab_01.cpp
g++ -o lab_01 lab_01.o -pthread
./lab_01
