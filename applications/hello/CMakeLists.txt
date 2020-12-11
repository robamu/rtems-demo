cmake_minimum_required(VERSION 3.15) 

# Disable these checks for RTEMS cross compiling, 
# which would be performed on the standard compiler
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)
set(CMAKE_CROSSCOMPILING 1)

project(hello)
add_executable(${CMAKE_PROJECT_NAME})

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}")
install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION "bin")

################################################################################
# Generic Project configuration
################################################################################

# Set a default build type if none was specified
set(DEFAULT_BUILD_TYPE "RelWithDebInfo")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS 
  	"Setting build type to '${DEFAULT_BUILD_TYPE}' as"
  	" none was specified."
  )
  set(CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
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
	message(FATAL_ERROR 
		"RTEMS configuration not found at "
		"${RTEMS_CONFIG_DIRECTORY}/RTEMSConfig.cmake"
	)
endif()

# Sanity checks
if(NOT RTEMS_PREFIX)
	message(FATAL_ERROR "No RTEMS prefix supplied!")
endif()

if(NOT RTEMS_BSP)
	message(FATAL_ERROR "No RTEMS BSP pair name supplied!")
endif()

include("${RTEMS_CONFIG_DIRECTORY}/RTEMSConfig.cmake")
rtems_general_config(${CMAKE_PROJECT_NAME} ${RTEMS_PREFIX} ${RTEMS_BSP})


################################################################################
# Application
################################################################################
		
target_sources(${CMAKE_PROJECT_NAME}
	PUBLIC
		init.c 
		hello.c
)
