#include<LPC17xx.h>
#define En 0x04;
void delay(unsigned long int x);
void lcdwrt(unsigned char y)
{
    LPC_GPIO2->FIOPIN0 = y;
    LPC_GPIO1->FIOSET1 = En;
    //delay(0x50000);
    LPC_GPIO1->FIOCLR1 = En;
    //delay(0x50000);
}
