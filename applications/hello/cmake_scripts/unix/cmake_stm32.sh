cmake -G "Unix Makefiles" -DRTEMS_VERSION=$RTEMS_VERSION -DRTEMS_BSP=arm/stm32h7 -DRTEMS_PREFIX=$RTEMS_TOOLS ..
cmake --build . $1
