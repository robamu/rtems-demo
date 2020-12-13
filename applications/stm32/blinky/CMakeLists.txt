cmake_minimum_required(VERSION 3.15) 

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)
set(CMAKE_CROSSCOMPILING 1)

project(blinky)

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

set(RTEMS_CONFIG_DIR
	"${CMAKE_CURRENT_SOURCE_DIR}/../../../rtems-cmake"
	 CACHE FILEPATH "Directory containing the RTEMS *.cmake files"
)

if(NOT EXISTS ${RTEMS_CONFIG_DIR}/RTEMSConfig.cmake) 
	message(FATAL_ERROR 
		"RTEMS configuration not found at"
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
		led.c 
		stm32h7xx_nucleo.c
)

add_custom_command(
	TARGET ${CMAKE_PROJECT_NAME}
	POST_BUILD
	COMMAND ${RTEMS_OBJCOPY} -O binary ${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}.bin
)
