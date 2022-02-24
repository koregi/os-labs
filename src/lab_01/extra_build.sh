#!/bin/bash

mkdir build -p
cd build
g++ -c ../extra_task_01.cpp
g++ -o extra_task_01 extra_task_01.o -pthread
./extra_task_01
