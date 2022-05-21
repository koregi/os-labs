#!/bin/bash

mkdir -p build && pushd build
g++ -o lab_07_1 ../lab_07_1.cpp -lpthread -lrt
sudo setcap cap_sys_resource=eip lab_07_1
./lab_07_1
popd