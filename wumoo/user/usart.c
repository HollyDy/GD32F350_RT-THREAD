#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "gd32f3x0.h"
#include "usart.h"
#include "gd32f3x0_usart.h"
#include "gd32f3x0_gpio.h"

void rt_Uart1Config(void)
{
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_USART1);

    /* connect port to USART1_Tx */
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_2);

    /* connect port to USARTx_R1 */
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_3);

    /* configure USART1 Tx as alternate function push-pull */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_2);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_2);

    /* configure USART2 Rx as alternate function push-pull */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_3);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_3);

    /* USART2 configure */
    usart_deinit(USART1);
    usart_baudrate_set(USART1,115200);
    usart_receive_config(USART1, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART1, USART_TRANSMIT_ENABLE);
    usart_enable(USART1);
}



void rt_Uart1WriteByte(char c)
{
    usart_data_transmit(USART1, c);
    while (RESET == usart_flag_get(USART1,USART_FLAG_TC));
}


void rt_Uart1WriteStr(const char* str)
{
    while (*str)
    {
        usart_data_transmit(USART1, * str++);
        while (RESET == usart_flag_get(USART1,USART_FLAG_TC));
    }
}



void rt_Uart1ReadByte(char* c)
{
    while (RESET == usart_flag_get(USART1,USART_FLAG_RBNE));
    *c = (usart_data_receive(USART1));
}


static char _buffer[256];
void rt_Uart1Printf(char* fmt, ...)
{
    int i;
    va_list ap;
    va_start(ap, fmt);
    vsprintf(_buffer, fmt, ap);
    va_end(ap);

    for (i = 0; _buffer[i] != '\0'; i++)
    {
        rt_Uart1WriteByte(_buffer[i]);
    }
}
