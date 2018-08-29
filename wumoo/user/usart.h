#ifndef __USART_H
#define __USART_H

void rt_Uart1Config(void);
void rt_Uart1ReadByte(char* c);
void rt_Uart1WriteByte(char c);
void rt_Uart1WriteStr(const char* str);

#endif
