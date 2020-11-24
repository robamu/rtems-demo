# RTEMS Test Repository

Just a personal test repository to get familiar with RTEMS.
It configured and built the RTEMS toolchain in the same path in
a folder named toolchain but I do not include them in the repo. 

There is a small helper file I use to add the built `erc32` BSP
to the path. It can be used like that

```sh
source pathhelper
```

## Demo Application

### Build demo application

The demo application is located inside the hello folder in the application folder.
It is compiled and can be run on a host computer with the `erc32-sis` simulator.

After installing the `sparc/erc32` BSP (instruction can be read in toolchain README), perform following steps to build the demo application.
The `$RTEMS_INST` variable shoulde be set to the RTEMS toolchain location, for example by running `export RTEMS_INST=$(pwd)/toolchain/rtems/6`

```sh
cd applications/hello
./waf configure --rtems=$RTEMS_INST --rtems-bsp=sparc/erc32
./waf
```

### Run demo application in simulator

The demo application can be run with the following command

```sh
cd applications/hello
$RTEMS_INST/bin/rtems-run --rtems-bsp=erc32-sis build/sparc-rtems6-erc32/hello.exe
```

## STM32 Test Application

### Build demo application

The STM32 application is located inside the hello_stm32 folder in the appkication folder. It is compiled with the `arm/stm32h7` BSP.

