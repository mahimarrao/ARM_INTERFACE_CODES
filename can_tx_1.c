#include<LPC17xx.h>
void CAN_Init(void);
void delay(unsigned long int z);
void can_tx(unsigned long int id,unsigned char msg);
unsigned char rx=0;
int main()
{
SystemInit ();	
CAN_Init();
	while(1)
	{
		
can_tx(0x00000020,'1');
		delay(0x50);
	}
}

void CAN_Init(void)

{
LPC_SC->PCONP|=0x00002000;
LPC_SC->PCLKSEL0|=0X00000000;
LPC_PINCON->PINSEL0|=0X00000005;
LPC_CAN1->MOD=0x00000001;
LPC_CAN1->CMR=0X00000000;
LPC_CAN1->GSR=0x00000000;
LPC_CAN1->IER=0x00000001;
LPC_CAN1->BTR=0X001C0007;
LPC_CAN1->MOD=0x00000000;	
}

void delay(unsigned long int z)
{unsigned long int x;
for(x=0;x<z;x++);
}

 
  void can_tx(unsigned long int id,unsigned char msg)
	{
	while((LPC_CAN1->SR&0X00000004)!=0X00000004);  // Transmitter buffer status = 1 
		LPC_CAN1->TFI1=0X80010000;   //  Transmit frame information , Frame formate = 29 bit ID ,data frame ,DLC = 1 Byte 
		LPC_CAN1->TID1=id;           //
		LPC_CAN1->TDA1=msg;          //  
		LPC_CAN1->CMR=0X21;          // command mode register TR:transmission request =1 , STB1 = 1 
		
	}
 
	