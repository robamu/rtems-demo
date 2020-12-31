cmake_minimum_required(VERSION 3.15) 

# Disable these checks for RTEMS cross compiling, 
# which would be performed on the standard compiler
# This is done to prevent CMake from supplying invalid 
# linker flags on Windows. 
# Besides, the target system is not the host system.
#set(CMAKE_SYSTEM_NAME Generic)
#set(CMAKE_C_COMPILER_WORKS TRUE)
#set(CMAKE_CXX_COMPILER_WORKS TRUE)
#set(CMAKE_CROSSCOMPILING TRUE)

################################################################################
# Load RTEMS configuration and checks
################################################################################

if(ENV{RTEMS_PREFIX}) 
	set(RTEMS_PREFIX $ENV{RTEMS_PREFIX} CACHE FILEPATH "RTEMS prefix")
endif()

if(ENV{RTEMS_BSP}) 
	set(RTEMS_BSP $ENV{RTEMS_BSP} CACHE STRING "RTEMS BSP pair")
endif()

if(ENV{RTEMS_VERSION})
	set(RTEMS_VERSION $ENV{RTEMS_VERSION} CACHE STRING "RTEMS version")
endif()

option(RTEMS_VERBOSE "Verbose output for the RTEMS CMake support" FALSE)

set(RTEMS_INSTALL 
	${CMAKE_INSTALL_PREFIX} 
	CACHE FILEPATH "RTEMS install destination"
)

if(NOT ENV{RTEMS_PATH})
	message(STATUS 
		"RTEMS path was not specified and was set to RTEMS prefix."
	)
	set(RTEMS_PATH ${RTEMS_PREFIX} CACHE FILEPATH "RTEMS folder")
endif()

if(NOT ENV{RTEMS_TOOLS})
	message(STATUS 
		"RTEMS toolchain path was not specified and was set to RTEMS prefix."
	)
	set(RTEMS_TOOLS ${RTEMS_PREFIX} CACHE FILEPATH "RTEMS tools folder")
endif()

if(NOT ENV{RTEMS_VERSION})
	message(STATUS "No RTEMS_VERSION supplied.")
    message(STATUS "Autodetermining version from tools path ${RTEMS_TOOLS} ..")
    string(REGEX MATCH [0-9]+$ RTEMS_VERSION "${RTEMS_TOOLS}")
    message(STATUS "Version ${RTEMS_VERSION} found")
endif()

set(RTEMS_VERSION "${RTEMS_VERSION}" CACHE STRING "RTEMS version")

message(STATUS "Setting up and checking RTEMS cross compile configuration..")

if(NOT ENV{RTEMS_ARCH_VERSION_NAME})
	
	string(REPLACE "/" ";" RTEMS_BSP_LIST_SEPARATED ${RTEMS_BSP})
	list(LENGTH RTEMS_BSP_LIST_SEPARATED BSP_LIST_SIZE)

	if(NOT ${BSP_LIST_SIZE} EQUAL 2)
    	message(FATAL_ERROR 
    		"Supplied RTEMS_BSP variable invalid. " 
    		"Make sure to provide a slash separated string"
    	)
	endif()

	list(GET RTEMS_BSP_LIST_SEPARATED 0 RTEMS_ARCH_NAME)
	list(GET RTEMS_BSP_LIST_SEPARATED 1 RTEMS_BSP_NAME)

	#set(RTEMS_ARCH_VERSION_NAME "${RTEMS_ARCH_NAME}-rtems${RTEMS_VERSION}")
	set(ENV{RTEMS_ARCH_VERSION_NAME} "${RTEMS_ARCH_NAME}-rtems${RTEMS_VERSION}")
endif()

set(RTEMS_CONFIG_DIR 
	"${CMAKE_CURRENT_SOURCE_DIR}/../../rtems-cmake" 
	CACHE FILEPATH 
	"Directory containing the RTEMS *.cmake files"
)

set(ENV{RTEMS_PREFIX} ${RTEMS_PREFIX})
set(ENV{RTEMS_BSP} ${RTEMS_BSP})
set(ENV{RTEMS_VERSION} ${RTEMS_VERSION})
set(ENV{RTEMS_BSP_NAME} ${RTEMS_BSP_NAME})
set(ENV{RTEMS_ARCH_NAME} ${RTEMS_ARCH_NAME})


set(CMAKE_TOOLCHAIN_FILE ${RTEMS_CONFIG_DIR}/RTEMSToolchain.cmake) 

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



if(NOT EXISTS ${RTEMS_CONFIG_DIR}/RTEMSConfig.cmake) 
	message(FATAL_ERROR 
		"RTEMS configuration not found at "
		"${RTEMS_CONFIG_DIR}/RTEMSConfig.cmake"
	)
endif()

# Sanity checks
if(NOT RTEMS_PREFIX)
	message(FATAL_ERROR "No RTEMS prefix supplied!")
endif()

if(NOT RTEMS_BSP)
	message(FATAL_ERROR "No RTEMS BSP pair name supplied!")
endif()

include("${RTEMS_CONFIG_DIR}/RTEMSConfig.cmake")
rtems_general_config(${CMAKE_PROJECT_NAME} ${RTEMS_PREFIX} ${RTEMS_BSP})


################################################################################
# Application
################################################################################
		
target_sources(${CMAKE_PROJECT_NAME}
	PUBLIC
		init.c 
		hello.c
)
