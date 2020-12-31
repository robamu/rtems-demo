#!/bin/sh
source_dir=$(cd ../ && pwd)

counter=0
if [ -z "$RTEMS_TOOLS" ]; then
	echo "RTEMS_TOOLS environmental variable (RTEMS prefix) has to be set!"
	exit 1
fi

if [ -z "$RTEMS_VERSION" ]; then
	echo "RTEMS_VERSION environmental variable not set. Will be autodetermined from tools path"
fi

while [ ${counter} -lt 5 ]
do
	cd ..
	if [ -d "rtems-cmake" ];then
		break
	fi
	counter=$((counter=counter + 1))
done

if [ "${counter}" -ge 5 ];then
	echo "create_cmake_cfg.sh not found in upper directories!"
	exit 1
fi

cd rtems-cmake

build_generator=""
if [ "${OS}" = "Windows_NT" ]; then
	build_generator="MinGW Makefiles"
# Could be other OS but this works for now.
else
	build_generator="Unix Makefiles"
fi

set -x # Print command 
echo "Running command (without the leading +):"
python3 cmake_build_config.py -p "${RTEMS_TOOLS}" -t "arm/stm32h7" -g "${build_generator}" -b "size" -s "${source_dir}"
# Use this if commands are added which should not be printed
# set +x