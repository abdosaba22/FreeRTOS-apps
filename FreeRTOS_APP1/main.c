/*
 * FreeRTOS_APP1.c
 *
 * Created: 9/30/2022 1:16:17 PM
 * Author : DELL
 */ 

#include "header.h"

TaskHandle_t task1handle = NULL;
TaskHandle_t task2handle = NULL;
/*  
RTOS_app Non-preemptive   
*/

void task1(void * p){
	uint8_t count1=0;
	while(1){
		
		LCD_write_command(0x80);
		
		LCD_write_string("from-task1:");
		LCD_write_num(count1);
		count1++;
		_delay_ms(10);
		vTaskDelay(1000);// 1s	
	}
}

void task2(void * p){
	uint8_t count2 =255;
	while (1)
	{
		LCD_write_command(0xC0);
		LCD_write_string("from-task2:");
		LCD_write_num(count2);
		count2--;
		_delay_ms(10);
		vTaskDelay(5000);// 5s
	}
}


int main(void)
{	LCD_init();
	LCD_write_string("HELLO_RTOS");
	_delay_ms(50);
	xTaskCreate(task1,"t1",100,NULL,1,task1handle);
    xTaskCreate(task2,"t2",100,NULL,1,task2handle);
	vTaskStartScheduler();
}

