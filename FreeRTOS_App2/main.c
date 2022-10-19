/*
 * FreeRTOS_App2.c
 *
 * Created: 9/30/2022 2:40:02 PM
 * Author : DELL
 */ 

#include "header.h"

/*************************

FreeRTOS App 2 preemptive 
using semaphore for guarding our shared resource LCD 

****************************/

TaskHandle_t task1handle=NULL;
TaskHandle_t task2handle=NULL;
TaskHandle_t task3handle=NULL;

SemaphoreHandle_t LCD_flag;

void task1(void * p){
	uint8_t task1numb=0;
	while (1)
	{
		if (xSemaphoreTake(LCD_flag,200))
		{
			LCD_write_command(0x80);
			LCD_write_string("from-task1:");
			LCD_write_num(task1numb);
			task1numb++;
			xSemaphoreGive(LCD_flag);
		}
		vTaskDelay(1000);	
	}
}

void task2(void * p){
	uint8_t task2numb=255;
	while (1)
	{
		if (xSemaphoreTake(LCD_flag,200))
		{
			LCD_write_command(0xC0);
			LCD_write_string("from-task2:");
			LCD_write_num(task2numb);
			task2numb--;
			xSemaphoreGive(LCD_flag);
		}
		vTaskDelay(1000);	
	}
}



void task3(void * p){
	CLRBIT(DDRB,0); // d=for switch ip
	SETBIT(PORTB,0); // pull up 
	SETBIT(DDRB,1); // for led	op
	while (1)
	{
		if(READBIT(PINB,0)==0){while(READBIT(PINB,0)==0); TOGBIT(PORTB,1);}
	}
	
}


int main(void)
{
    LCD_init();
	LCD_write_command(0x80);
	LCD_write_string("Hello-RTOS-2");
	_delay_ms(1000);
	LCD_flag =xSemaphoreCreateBinary();
	xSemaphoreGive(LCD_flag);
	
	
	xTaskCreate(task1,"t1",100,(void *)0,1,task1handle);
	xTaskCreate(task2,"t2",100,(void *)0,1,task1handle);
	xTaskCreate(task3,"t3",100,(void *)0,1,task1handle);
	vTaskStartScheduler();
}

