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
		char arr1[3][13] = {"7500398BBC7B\0","840085AE6AC5\0","840085A9C46C\0"},msg1[]="valid",msg2[]="invalid";
		char arr[12];
	
		
		SystemInit();
		
		//Uart intialization
		LPC_PINCON->PINSEL0 |= 0x00000050;
    uart_init();
		
		//Uart3 intialization
		LPC_SC->PCONP |= 0x02000000;
		LPC_PINCON->PINSEL9|= 0x0F000000;
		uart3_init();
	  
		//led intialization
		LPC_GPIO1->FIOMASK3 = 0xEF;
    LPC_GPIO1->FIODIR3 = 0x10;
		
		while(1)
    {
			int i=0,j=0,l=0;
			int flag=0;
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
			
			//displaying it back
			for(i=0; arr[i]!='\0' ; i++)
      { LPC_UART0->THR = arr[i];
			  while((LPC_UART0->LSR&0x20) != 0x20)
				{}
      }	
			next();
			
			//l=strlen(arr1[0]);
			arr1[0][0]='7';
			for(i=0;i<3;i++)
			{
				j=0;
				while(arr1[i][j]!='\0')
				{  
					if(arr[j] != arr1[i][j])
					{
							flag = 1;
							break;
					}
					j++;
				}
				if(j==l)
				{
					flag=0;
					break;
				}

			}
				if(flag == 0)
				{
							LPC_GPIO1->FIOSET3 = 0x10;
							delay(500);
					    display(msg1,0,'\0');
					    next();
					}
					else
						
					{
							LPC_GPIO1->FIOCLR3 = 0x10;
							delay(500);
						  display(msg2,0,'\0');
					    next();
							
					}
				}
	
    }

void next()
{
	LPC_UART0->THR = 0x0D;
	while((LPC_UART0->LSR&0x20) != 0x20){}
	LPC_UART0->THR = 0x0A;
	while((LPC_UART0->LSR&0x20) != 0x20){}
}

void display(char arr[],int s,int e)
{
	int i;
	for(i=s; arr[i]!=e ; i++)
				{ 
					LPC_UART0->THR = arr[i];
					while((LPC_UART0->LSR&0x20) != 0x20)
					{}
				}	
}
			
	
	