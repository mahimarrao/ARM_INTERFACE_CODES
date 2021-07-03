#include<stdio.h>
#include<LPC17xx.h>
#include<string.h>
void delay(unsigned long int x);
void uart_init(void);
int main ()
{
		char arr1[4][6] = { "43460","36029","44650","35772"},arr[10]="WELCOME",i;
		SystemInit();
		
		//Uart3 intialization
		LPC_SC->PCONP |= 0x02000000;
		LPC_PINCON->PINSEL9|= 0x0F000000;
		uart_init();
	  
		//led intialization
		LPC_GPIO1->FIOMASK3 = 0xEF;
		LPC_GPIO1->FIODIR3 = 0x10; 
		
		for(i=0; arr[i]!='\0' ; i++)
			{ LPC_UART3->THR = arr[i];
			  while((LPC_UART3->LSR&0x20) != 0x20)
			  {}
			}	
			
		
}		
			
	
	