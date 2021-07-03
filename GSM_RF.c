#include<stdio.h>
#include<LPC17xx.h>
#include<string.h>
void delay(unsigned long int x);
void uart_init(void);
void uart3_init(void);
void display(char arr[],int s,int e);
void next();
int main ()
{
	char arr1[10][100] = {"AT\r\n","AT+CREG?\r\n","AT+CGATT=1\r\n","AT+CIPSHUT\r\n","AT+CIPMUX=0\r\n","AT+CSTT=\"jionet\",\" \",\" \"\r\n","AT+CIICR\r\n","AT+CIFSR\r\n","AT+CIPSTART=\"TCP\",\"192.168.0.1\",\"19900\"\r\n","AT+CIPSEND\r\n"};
    //char arr1[5][30] = {"AT\r\n","AT+CREG?\r\n","AT+CMGF=1\r\n","AT+CMGS=\"6363089373\"\r\n"};
	  char arr[12];
    char msg[4][20]={"1","Pearl millet","2","all"};
	  
		
		SystemInit();
		
		//Uart0 intialization
		LPC_PINCON->PINSEL0 |= 0x00000050;
    uart_init();
		
		//UART3 intialization
		LPC_SC->PCONP |= 0x02000000;
		LPC_PINCON->PINSEL9|= 0x0F000000;
		
		uart3_init();
		
		//while(1)
		{
		int l=0;
		
	  int val=0;
		
			//recieving the data 
			while(l!=12)
			{
				while((LPC_UART0->LSR&0x01)!=0x01){}
        val = LPC_UART0->RBR;
        arr[l]=val;
				l++;
				
			}
			arr[l]=0x0D;
			arr[l]='\0';
		}
		
    {
			int i=0,j=0;
			
			//int val;
		
			
       // sending
			for(j=0;j<10;j++)
			{
				
				
			for(i=0; arr1[j][i]!='\0' ; i++)
			
      { LPC_UART0->THR = arr1[j][i];
			  while((LPC_UART0->LSR&0x20) != 0x20)
				{}
			}
			j++;
			//next();
			//delay(0x500000);
				
			
			
			if(j==9)
				{ for(j=0;j<5;j++)
					{
					for(i=0; msg[j][i]!='\0' ; i++)
			
        { 
				LPC_UART0->THR = msg[j][i];
			  while((LPC_UART0->LSR&0x20) != 0x20)
				{}
				}
			}
				  for(i=0; arr[i]!='\0' ; i++)
			
        { 
				LPC_UART0->THR = msg[0][i];
			  while((LPC_UART0->LSR&0x20) != 0x20)
				{}
				}
				
				LPC_UART0->THR = 0x1A;
			  while((LPC_UART0->LSR&0x20) != 0x20)
				{}
				//delay(0x500000);
				}
			      	
			
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