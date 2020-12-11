cmake -DRTEMS_BSP=arm/stm32h7 -DRTEMS_TOOLS=$RTEMS_INST ..

cmake --build . $1
