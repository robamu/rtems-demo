cmake -DRTEMS_VERSION=6 -DRTEMS_BSP=arm/stm32h7 -DRTEMS_PREFIX=$RTEMS_TOOLS  ..

cmake --build . $1
