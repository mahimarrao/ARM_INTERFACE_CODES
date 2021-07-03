#include<stdio.h>
#include<LPC17xx.h>
#include<string.h>
void delay(unsigned long int x);
void uart_init(void);
void UART3_init(void);
void display(char arr[],int s,int e);
void next();
int main ()
{
		char arr1[5][30] = {"AT\r\n","AT+CREG?\r\n","AT+CMGF=1\r\n","AT+CMGS=\"6363089373\"\r\n"};
		//char arr[12];
    char msg[][5]={"hello",0x1A};
	
		
		SystemInit();
		
		//Uart intialization
		LPC_PINCON->PINSEL0 |= 0x00000050;
    uart_init();
		
		//UART0 intialization
		LPC_SC->PCONP |= 0x02000000;
		LPC_PINCON->PINSEL9|= 0x0F000000;
	//	UART3_init();
		
		//while(1)
    {
			int i=0,j,c;
			//int val;
		
			
       // sending
			for(j=0;j<4;j++)
			{
				
				
			for(i=0; arr1[j][i]!='\0' ; i++)
			
      { LPC_UART0->THR = arr1[j][i];
			  while((LPC_UART0->LSR&0x20) != 0x20)
				{}
			}
			//next();
			delay(0x500000);
				
			
			
			if(j==3)
				{
					for(i=0; msg[0][i]!='\0' ; i++)
			
        { 
				LPC_UART0->THR = msg[0][i];
			  while((LPC_UART0->LSR&0x20) != 0x20)
				{}
				}
				LPC_UART0->THR = 0x1A;
			  while((LPC_UART0->LSR&0x20) != 0x20)
				{}
				delay(0x500000);
				}
			      	
			//delay(0x30000);
		
			
//			//recieving the data 
//       i=0;
//			 c=0;
//		   while(c!=2)
//			{
//				while((LPC_UART0->LSR&0x01)!=0x01){}
//        val = LPC_UART0->RBR;
//        arr[i]=val;
//				i++;
//				if(val==0x0A)
//				{c++;}
//				
//			}
//		
//			arr[i]='\0';
//			next();
//			
//			//displaying it back
//			for(i=0; arr[i]!='\0' ; i++)
//      { LPC_UART0->THR = arr[i];
//			  while((LPC_UART0->LSR&0x20) != 0x20)
//				{}
//      }	
//			next();
		}
		}
	}		
	
	void next()
{
//	LPC_UART0->THR = 'x';
//	while((LPC_UART0->LSR&0x20) != 0x20){}
	LPC_UART0->THR = 0x0D;
	while((LPC_UART0->LSR&0x20) != 0x20){}
	LPC_UART0->THR = 0x0A;
	while((LPC_UART0->LSR&0x20) != 0x20){}
}