cmake -DRTEMS_PREFIX=$RTEMS_TOOLS -DRTEMS_BSP=sparc/leon3  ..
cmake --build . $1
