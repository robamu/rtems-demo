#include "led.h"
#include "stm32h7xx_nucleo.h"

#include <stdio.h>
#include <bsp.h>
#include <rtems.h>


rtems_task Init(rtems_task_argument argument) {
	rtems_status_code status;

	BSP_LED_Init(LED1);
	BSP_LED_Init(LED2);
	BSP_LED_Init(LED3);

	while (1) {
		(void) rtems_task_wake_after( 0.3 * rtems_clock_get_ticks_per_second() );
		BSP_LED_Toggle(LED1);
		BSP_LED_Toggle(LED2);
		BSP_LED_Toggle(LED3);
	}

	status = rtems_task_delete( RTEMS_SELF );
}

/**************** START OF CONFIGURATION INFORMATION ****************/

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MAXIMUM_TASKS             1

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INIT
#include <rtems/confdefs.h>

/****************  END OF CONFIGURATION INFORMATION  ****************/
