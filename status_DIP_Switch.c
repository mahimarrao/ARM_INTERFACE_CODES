#include<LPC17xx.h>
unsigned char sw;
int main(void)
{ 
SystemInit();
LPC_GPIO1->FIOMASK3=0XEF;  // 1110 1111 
LPC_GPIO1->FIODIR3=0X10;// 0001 0000
LPC_GPIO0->FIOMASK3=0XF7;
LPC_GPIO0->FIODIR3=0XF7; 
while(1)
{
	sw=((LPC_GPIO0->FIOPIN3 & 0x08) >>3);
	if(sw== 0X01)
	{
	LPC_GPIO1->FIOSET3=0X10;
	}
	else
	{
	LPC_GPIO1->FIOCLR3=0X10;
	}
}
}
