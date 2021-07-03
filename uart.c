#include<LPC17xx.h>
//void delay(unsigned long int x);
//void uart_init(void);
void uart_b()
int main()
{
    unsigned int  i;
    SystemInit();
    LPC_PINCON->PINSEL0 |= 0x00000050;
    uart_b();

    for(i=0; str[i]!='\0' ; ++i)
    {
			  while(LPC_UART0->LSR&0x20 != 0x20){
        LPC_UART0->THR = *str[i];
        }
					
    }
		
    return 0;
}

//void uart_init()
//{
//    LPC_UART0->LCR = 0x83;
//    LPC_UART0->DLM = 0x00;
//    LPC_UART0->DLL = 0x75;
//    LPC_UART0->FDR = 0x00000010;
//    LPC_UART0->LCR = 0x03;
//}

//void delay(unsigned long int x)
//{
//    unsigned long int i;
//    for(i=0;i<=x;++i);
//}

