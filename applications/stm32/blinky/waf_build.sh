#!/bin/bash

./waf configure --rtems=$RTEMS_INST --rtems-bsp=arm/stm32h7
./waf clean
./waf 

