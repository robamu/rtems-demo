/*
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 */

#include <stdio.h>
#include <bsp.h>
#include <rtems.h>
#include "led.h"

bool printoutEnabled = false;

rtems_task Init(rtems_task_argument argument)
{
  rtems_status_code status;

  ledInit();

  while (1) {

    (void) rtems_task_wake_after( 1 * rtems_clock_get_ticks_per_second() );
    ledOff();
    if(printoutEnabled) {
    	printf("LED Off\n\r");
    }
    (void) rtems_task_wake_after( 1 * rtems_clock_get_ticks_per_second() );
    ledOn();
    if(printoutEnabled) {
    	printf("LED On\n\r");
    }

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
