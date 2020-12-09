cmake_minimum_required(VERSION 3.13) 

project(blinky)

#############################################
# This part should be moved to separate file
#############################################

set(RTEMS_INST "Test" CACHE STRING "RTEMS Toolchain installation path")
set(RTEMS_BSP "sparc/erc32" CACHE STRING "RTEMS BSP")
set(RTEMS_VERSION "6" CACHE STRING "RTEMS version")

if (RTEMS_INST STREQUAL "")
	message(FATAL_ERROR "RTEMS toolchain path has to be specified!")
endif()  

if(RTEMS_BSP STREQUAL "arm/stm32h7")
set(RTEMS_ARCH_NAME "arm")
set(RTEMS_BSP_NAME "stm32h7")

endif()

set(RTEMS_ARCH_TOOLS "${RTEMS_ARCH_NAME}-rtems${RTEMS_VERSION}")


if(IS_DIRECTORY "${RTEMS_INST}/${RTEMS_ARCH_TOOLS}")
	set(RTEMS_BSP_LIB_PATH "${RTEMS_INST}/${RTEMS_ARCH_TOOLS}/${RTEMS_BSP_NAME}/lib")
	if(NOT IS_DIRECTORY "${RTEMS_BSP_LIB_PATH}") 
		message(FATAL_ERROR "RTEMS BSP lib folder not found at ${RTEMS_BSP_LIB_PATH}")
	endif()
	set(RTEMS_BSP_INC_PATH "${RTEMS_BSP_LIB_PATH}/include")
	if(NOT IS_DIRECTORY "${RTEMS_BSP_INC_PATH}")
		message(FATAL_ERROR "RTEMS BSP include folder not found at ${RTEMS_BSP_INC_PATH}")
	endif()
else()
	message(FATAL_ERROR "RTEMS Architecure folder not found at ${RTEMS_INST}/${RTEMS_ARCH_TOOLS}")
endif()

###################################
# Checking for toolchain binaries
###################################

set(RTEMS_BIN_PATH "${RTEMS_INST}/bin")
if(NOT IS_DIRECTORY "${RTEMS_BIN_PATH}")
	message(FATAL_ERROR "RTEMS binaries folder not found at ${RTEMS_INST}/bin")
endif()

set(RTEMS_GCC "${RTEMS_BIN_PATH}/${RTEMS_ARCH_TOOLS}-gcc")
if(NOT EXISTS "${RTEMS_GCC}") 
	message(FATAL_ERROR "RTEMS gcc compiler not found at ${RTEMS_BIN_PATH}/${RTEMS_ARCH_TOOLS}-gcc")
endif()

set(RTEMS_GXX "${RTEMS_BIN_PATH}/${RTEMS_ARCH_TOOLS}-g++")
if(NOT EXISTS "${RTEMS_GXX}")
	message(FATAL_ERROR "RTEMS g++ compiler not found at ${RTEMS_BIN_PATH}/${RTEMS_ARCH_TOOLS}-g++")
endif()

set(RTEMS_ASM "${RTEMS_BIN_PATH}/${RTEMS_ARCH_TOOLS}-as")
if(NOT EXISTS "${RTEMS_GXX}")
	message(FATAL_ERROR "RTEMS as compiler not found at ${RTEMS_BIN_PATH}/${RTEMS_ARCH_TOOLS}-as")
endif()

set(RTEMS_LD "${RTEMS_BIN_PATH}/${RTEMS_ARCH_TOOLS}-ld")
if(NOT EXISTS "${RTEMS_LD}")
	message(FATAL_ERROR "RTEMS ld linker  not found at ${RTEMS_BIN_PATH}/${RTEMS_ARCH_TOOLS}-ld")
endif()

if(${RTEMS_ARCH_NAME} STREQUAL "arm")
set(CMAKE_SYSTEM_PROCESSOR arm)
endif()

set(CMAKE_C_COMPILER "${RTEMS_GCC}")
set(CMAKE_CXX_COMPILER "${RTEMS_GXX}")
set(CMAKE_ASM_COMPILER "${RTEMS_ASM}")


############################################
# Info output
###########################################

message(STATUS "RTEMS Version: ${RTEMS_VERSION}")
message(STATUS "RTEMS installation path: ${RTEMS_INST}")
message(STATUS "RTEMS Architecture tools path: ${RTEMS_ARCH_TOOLS}")
message(STATUS "RTEMS BSP: ${RTEMS_BSP}")
message(STATUS "RTEMS BSP LIB path: ${RTEMS_BSP_LIB_PATH}")
message(STATUS "RTEMS BSP INC path: ${RTEMS_BSP_INC_PATH}")

message(STATUS "RTEMS gcc Compiler: ${RTEMS_GCC}")
message(STATUS "RTEMS g++ compiler: ${RTEMS_GXX}")


# Here comes application stuff again

add_executable(${CMAKE_PROJECT_NAME} init.c led.c stm32h7xx_nucleo.c)

set(RTEMS_LIB_NAME "rtems_${RTEMS_ARCH_NAME}_${RTEMS_BSP_NAME}")
add_library(${RTEMS_LIB_NAME} SHARED IMPORTED)
set_target_properties(${RTEMS_LIB_NAME} PROPERTIES
	IMPORTED_LOCATION ${RTEMS_BSP_LIB_PATH}
)

#target_link_directories(${RTEMS_LIB_NAME} INTERFACE
#	${RTEMS_BSP_LIB_PATH}
#)
target_include_directories(${RTEMS_LIB_NAME} INTERFACE
	${RTEMS_BSP_INC_PATH}
)
target_link_options(${RTEMS_LIB_NAME} INTERFACE
#	-I${RTEMS_BSP_INC_PATH}
#	-B${RTEMS_BSP_LIB_PATH}
	-Wl,--gc-sections 
	-Wl,-Bstatic 
	-Wl,-Bdynamic 
	-qrtems
)

target_link_libraries(${CMAKE_PROJECT_NAME} ${RTEMS_LIB_NAME})

if(RTEMS_BSP STREQUAL "arm/stm32h7")
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC 
	-mthumb
	-mcpu=cortex-m7
	-mfpu=fpv5-d16
	-mfloat-abi=hard
)

target_link_options(${CMAKE_PROJECT_NAME} BEFORE PUBLIC 
	-mthumb
	-mcpu=cortex-m7
	-mfpu=fpv5-d16
	-mfloat-abi=hard
)


endif()
		
