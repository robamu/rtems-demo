/*
 * Hello world example
 */
#include <rtems.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

rtems_task Init(
  rtems_task_argument ignored
)
{  
	printf( "\nHello World\n" );
	for(;;) {
		sleep(100);
		printf("Alive!\n\r");
	}
	exit( 0 );

}
