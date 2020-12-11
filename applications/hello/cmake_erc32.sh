cmake -DRTEMS_PREFIX=$RTEMS_TOOLS -DRTEMS_BSP=sparc/erc32  ..
cmake --build . $1
