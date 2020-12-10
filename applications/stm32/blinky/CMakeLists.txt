cmake_minimum_required(VERSION 3.13) 

project(blinky)

add_executable(${CMAKE_PROJECT_NAME})

set(RTEMS_CONFIG_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../rtems-cmake" CACHE FILEPATH "Directory containing the RTEMS *.cmake files")

# If this directory is not set, it is assumed that the RTEMS config files are
# located in the current directory.
if(NOT RTEMS_CONFIG_DIRECTORY)
	set(RTEMS_CONFIG_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

################################################################################
# Load RTEMS configuration and checks
################################################################################

if(NOT EXISTS ${RTEMS_CONFIG_DIRECTORY}/RTEMSConfig.cmake) 
	message(FATAL_ERROR "RTEMS configuration not found at ${RTEMS_CONFIG_DIRECTORY}/RTEMSConfig.cmake")
endif()
include("${RTEMS_CONFIG_DIRECTORY}/RTEMSConfig.cmake")
rtems_general_config(${CMAKE_PROJECT_NAME} ${RTEMS_INST} ${RTEMS_BSP})

################################################################################
# Application
################################################################################
		
target_sources(${CMAKE_PROJECT_NAME}
	PUBLIC
		init.c 
		led.c 
		stm32h7xx_nucleo.c
)
