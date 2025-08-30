#ifndef __UART_H
#define __UART_H

void UART_Init(void);
void UART_Transmit(unsigned char data_);
unsigned char UART_Receive(void);

#endif
