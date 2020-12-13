# RTEMS Test Repository

Just a personal test repository to get familiar with RTEMS.
I configured and built the RTEMS toolchain in the same path in
a folder named toolchain but I do not include them in the repo. 
The toolchain folder contains instruction on how to build the 
toolchain if required.

There is a small helper file I use to configure the system path
called `path_setter_v<VersionNumber>` . 
Those can be used by running

```sh
source path_setter_v6
``` 

Also, don't forget to clone the submodules if you want to try out
this repository:

```sh
git submodule init
git submodule update
```

This will clone the application RTEMS `waf` and `CMake` support,
`waf` itself

I am going to assume that the RTEMS tools (e.g. cross compilers) and BSPs were already installed.
If this is not the case, it is recommended to clone the [toolchain repository](https://github.com/rmspacefish/rtems-tools.git) in the same folder this demo repository was
cloned and following the steps in the `README` to install all required tools and BSPs.

## Demo Application

### Build demo application

The demo application is located inside the hello folder in the application folder.
It is compiled and can be run on a host computer with the `erc32-sis` simulator.

After installing the `sparc/erc32` BSP (instruction can be read in toolchain README), perform following steps to build the demo application.
The `$RTEMS_INST` variable shoulde be set to the RTEMS toolchain location, for example by running `export RTEMS_INST=$(pwd)/toolchain/rtems/6`

```sh
cd applications/hello
./waf configure --rtems=$RTEMS_TOOLS --rtems-bsp=sparc/erc32
./waf
```

Alternatively, build with CMake:

```sh
mkdir Debug
cd Debug
cmake -DRTEMS_INST=$RTEMS_TOOLS -DRTEMS_BSP=sparc/erc32 ..
cmake --build . 
```



### Run demo application in simulator

The demo application can be run with the following command

```sh
cd applications/hello
$RTEMS_INST/bin/rtems-run --rtems-bsp=erc32-sis build/sparc-rtems6-erc32/hello.exe
```

## STM32H743ZI Nucleo Test Application

### Build demo application

The STM32 application is located inside the stm32/blinky folder in the application folder. It is compiled with the `arm/stm32h7` BSP.
It is assumed that the RTEMS ARM toolchain binaries have been added to the path.

```sh
cd applications/stm32/blinky
./waf configure --rtems=$RTEMS_TOOLS --rtems-bsp=arm/stm32h7
./waf
```

The shell script `build.sh` has been provided to perform all steps at once. 

Alternatively, build with CMake:

```sh
mkdir Debug
cd Debug
cmake -DRTEMS_TOOLS=$RTEMS_TOOLS -DRTEMS_BSP=arm7/stm32h7 ..
cmake --build . 
```


The resulting binary will be linked for flash memory and can be flashed via OpenOCD, drag and drop (binary to connected device) or the STM Cube Flash tools.

### Use Eclipse and configure to flash with OpenOCD

It is possible to use Eclipse together with the waf build system. OpenOCD was used to flash the STM32 with the binary and the debug it with `arm-rtems6-gdb` .
A `.project` and `.cproject` file is supplied in the blinky project to have a starting point. It is recommended to copy those from the eclipse folder into the blinky folder and then import the project in Eclipse.

It is recommended to set the `RTEMS_INST`, `RTEMS_BIN` and `RTEMS_PATH` variables in Eclipse. It should be in principle sufficient to set `RTEMS_PATH` properly. This is required so that Eclipse can find the installed toolchains and add them to the includes. The project files provide a starting point.

Cleaning and performing the configuration will be done by specific build targets `configure` and `clean`, which execute the respective commands from above. The build is performed by simply running `waf` instead of `make` as the build command.

The xPacks OpenOCD software will be used to flash the board. It can be installed with the xpm packet manager.

1. Install npm (NodeJS on Windows)
2. Install xpm
    ```sh
    npm install --global xpm
    ```

3. Install OpenOCD
    ```sh
    xpm install --global @xpack-dev-tools/openocd@latest
    ```
    
4. Install the MCU plugin for Eclipse. After that, check whether the OpenOCD plugin is found in Eclipse by going to Windows &rarr; Preferences &rarr; MCU and check whether the path is found

5. Add the install path of OpenOCD to the system path by adding `export PATH=$PATH:<..../@gnu-mcu-eclipse/open-ocd/<version>/.content/bin>` to the `.profile` file on Linux
