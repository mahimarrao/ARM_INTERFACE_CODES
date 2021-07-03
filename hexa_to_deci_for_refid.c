#include<stdio.h>
#include<LPC17xx.h>
#include <stdlib.h>
#include<string.h>
unsigned char a[] = "7500398BBC7B";
char* itoa(int num, char* str);
void reverse(char str[], int length);
int cal(int l,int k);
void uart_init(void);
int main()
{
	char i;
	char last[6],first[4]; 
	itoa(cal(9,5),last);
	itoa(cal(5,3),first);
	
		SystemInit();
		
		//Uart intialization
		LPC_PINCON->PINSEL0 |= 0x00000050;
    uart_init();
	
	  for(i=0; last[i]!='\0' ; i++)
			{ 
			  while((LPC_UART0->LSR&0x20) != 0x20)
			  {}
					LPC_UART0->THR = last[i];
				}		
return 0;
}

int  cal(int l,int k)
{
	char i,j=0,s=0;
	for(i=l;i>k;i--)
	{
		if(a[i]>=0x30 && a[i]<=0x39)
		{
			a[i]=a[i]-0x30;
		}
		if(a[i]>=0x41 && a[i]<=0x46)
		{
			a[i]=a[i]-0x31;
		}
		s+=a[i]*22^(j);
		j++;
	}
	
	return s;
}

char* itoa(int num, char* str) 
{ 
    int i = 0; 
    // Process individual digits 
    while (num != 0) 
    { 
        int rem = num % 10; 
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0'; 
        num = num/10; 
    } 
    
  
    str[i] = '\0'; // Append string terminator 
  
    // Reverse the string 
    reverse(str, i); 
  
    return str; 
} 
void reverse(char str[], int length) 
{ 
    int start = 0; 
    int end = length -1; 
	  int t;
    while (start < end) 
    { 
        t=*(str+start);
			  str[start]= *(str+end); 
			  str[end] = t;
			
        start++; 
        end--; 
    } 
}
