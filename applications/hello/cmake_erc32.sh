# TODO: Only builds release, read second command line argument to parse command line arguments to
# that is can build multiple configuratios?      
cmake -DRTEMS_VERSION=6 -DRTEMS_TOOLS=$RTEMS_TOOLS -DRTEMS_BSP=sparc/erc32 -DRTEMS_BSP_PATH=$RTEMS_SPARC_ERC32_BSP ..
cmake --build . $1
