
#include <rtthread.h>
#include "gd32f3x0.h"
#include "led.h"
#include "usart.h"

extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];


struct rt_thread rt_led1_thread;
struct rt_thread rt_led2_thread;

ALIGN(RT_ALIGN_SIZE)

rt_uint8_t rt_led1_thread_stack[512];
rt_uint8_t rt_led2_thread_stack[512];

void led1_thread_entry(void *p_arg);
void led2_thread_entry(void *p_arg);


void delay(uint32_t count);

int main(void)
{	
	rt_LedConfig(); 
	rt_Uart1Config();
	
	rt_system_scheduler_init();
	
	rt_thread_init( &rt_led1_thread,                 
	                led1_thread_entry,               
	                RT_NULL,                          
	                &rt_led1_thread_stack[0],        
	                sizeof(rt_led1_thread_stack) );  
	
	rt_list_insert_before( &(rt_thread_priority_table[0]),&(rt_led1_thread.tlist) );
	
	
	rt_thread_init( &rt_led2_thread,                 
	                led2_thread_entry,               
	                RT_NULL,                          
	                &rt_led2_thread_stack[0],       
	                sizeof(rt_led2_thread_stack) );  
	
	rt_list_insert_before( &(rt_thread_priority_table[1]),&(rt_led2_thread.tlist) );
	
	
	rt_system_scheduler_start(); 
}


void delay (uint32_t count)
{
	for(; count!=0; count--);
}


void led1_thread_entry( void *p_arg )
{
	for( ;; )
	{	
		rt_LedControl(LED1,LED_ON);
		rt_Uart1WriteStr("led1 on\r\n");
		delay(0xfffff);
		rt_LedControl(LED1,LED_OFF);
		rt_Uart1WriteStr("led1 off\r\n");
		delay(0xfffff);
		
				
		rt_schedule();
	}
}

void led2_thread_entry( void *p_arg )
{
	for( ;; )
	{		
		rt_LedControl(LED2,LED_ON);
		rt_Uart1WriteStr("led2 on\r\n");
		delay(0xfffff);
		rt_LedControl(LED2,LED_OFF);
		rt_Uart1WriteStr("led2 off\r\n");
		delay(0xfffff);
		
		rt_schedule();
	}
}

