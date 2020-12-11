cmake_minimum_required(VERSION 3.15) 

project(hello)
add_executable(${CMAKE_PROJECT_NAME})

install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION "bin")

################################################################################
# Generic Project configuration
################################################################################

if(NOT CMAKE_BUILD_TYPE)
	# Possible options: Release, Debug, RelWithDebInfo and MinSizeRel
	set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

################################################################################
# Load RTEMS configuration and checks
################################################################################

set(RTEMS_CONFIG_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../rtems-cmake" CACHE FILEPATH "Directory containing the RTEMS *.cmake files")

# If this directory is not set, it is assumed that the RTEMS config files are
# located in the current directory.
if(NOT RTEMS_CONFIG_DIRECTORY)
	set(RTEMS_CONFIG_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

if(NOT EXISTS ${RTEMS_CONFIG_DIRECTORY}/RTEMSConfig.cmake) 
	message(FATAL_ERROR "RTEMS configuration not found at ${RTEMS_CONFIG_DIRECTORY}/RTEMSConfig.cmake")
endif()

# Sanity checks
if(NOT RTEMS_TOOLS)
	message(FATAL_ERROR "No RTEMS tools path supplied!")
endif()

if(NOT RTEMS_BSP)
	message(FATAL_ERROR "No RTEMS BSP pair name supplied!")
endif()

include("${RTEMS_CONFIG_DIRECTORY}/RTEMSConfig.cmake")
if(DEFINED RTEMS_BSP_PATH)
rtems_general_config(${CMAKE_PROJECT_NAME} ${RTEMS_TOOLS} ${RTEMS_BSP} ${RTEMS_BSP_PATH})
else()
rtems_general_config(${CMAKE_PROJECT_NAME} ${RTEMS_TOOLS} ${RTEMS_BSP})
endif()


################################################################################
# Application
################################################################################
		
target_sources(${CMAKE_PROJECT_NAME}
	PUBLIC
		init.c 
		hello.c
)
