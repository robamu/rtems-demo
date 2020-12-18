cmake -G "Unix Makefiles" -DRTEMS_PREFIX=$RTEMS_TOOLS -DRTEMS_BSP=sparc/leon3 -DRTEMS_VERSION=$RTEMS_VERSION ..
cmake --build . $1
