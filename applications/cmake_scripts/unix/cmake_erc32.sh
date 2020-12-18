cmake -G "Unix Makefiles" -DRTEMS_PREFIX=$RTEMS_TOOLS -DRTEMS_BSP=sparc/erc32 -DRTEMS_VERSION=$RTEMS_VERSION ..
cmake --build . $1
