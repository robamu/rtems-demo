## Building RTEMS

I built the RTEMS toolchain in this folder like
specified in the [Quick Start](https://docs.rtems.org/branches/master/user/start/index.html).

## Prerequisites

## Ubuntu
Flex and Bison are used. Furthermore, the python-dev package should be installed.

```sh
sudo apt-get install flex bison python-dev
```

## Installing RTEMS on Ubuntu

### 1. Setting installation prefix

Set the installation prefix. In this case, use the current folder
and run

```sh
export RTEMS_HOME=$(pwd)/rtems/5
```

Test with `echo $RTEMS_HOME`

### 2. Obtain the sources

I used the Releases for now as specified in 
[the quickstart guide](https://docs.rtems.org/branches/master/user/start/sources.html)

```sh
mkdir src
cd src
curl https://ftp.rtems.org/pub/rtems/releases/5/5.1/sources/rtems-source-builder-5.1.tar.xz | tar xJf -
```

### 3. Install the Tool Suite

Installation is performed with the following command
as long as the `RTEMS_HOME` variable has been set properly.

```sh
cd src/rsb/rtems
../source-builder/sb-set-builder --prefix=$RTEMS_HOME 5/rtems-sparc
```

Succesfull installation can be verified with
```sh
$RTEMS_HOME/bin/sparc-rtems5-gcc --version
```

### 4. Build a Board Support Package (BSP)
