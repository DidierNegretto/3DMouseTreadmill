#!/bin/bash
# Script for compiling and running test before compilation
# of the STM32 code and upload.
echo PRE-BUILD STEPS
echo CLEANING TESTS
make clean -C ../../CodeSTM32/test/Debug/
echo COMPILING TESTS
make all -C ../../CodeSTM32/test/Debug/
echo RUNNING TESTS
./../../CodeSTM32/test/Debug/test

