#include<LPC17xx.h>

void uart_init()
{
    LPC_UART0->LCR = 0x83;
    LPC_UART0->DLM = 0x00;
    LPC_UART0->DLL = 0x75;
    LPC_UART0->FDR = 0x00000010;
    LPC_UART0->LCR = 0x03;
}

