//Aim: Read Analog Input by varying Potentiometer connected at P1.31(A0.5) & Compare the Measure Value (MV)
//with Reference Value (RV) to Energize or De-Energize the Relay connected to P0.22 through NPN transistor 
//as a Driver.
//------------------------------------------------------------------------------------------------------------------
//In ADC Initilization 
//i)   Enable the Power by setting PCAD=1 which is PCONP[12] 
//ii)  Select the 3rd alternate of P1.31 as it has to function as AIN.5 
//iii) Initilze ADC Control Register ADCR to a) Enable AIN.5 b) Divide PCLK_ADC by 4 using CLKDIV bits, 
//     Burst=1 for Continuous Scanning and Converting with START=000b and PDN=1 to enable Power Internally
//     To use Relay, Enable P0.22 using FIOMASK2[23:16]=1011 1111 -Setting bit FIOMASK2[22]=0 and Set the direction 
//     of P0.22 as Output using FIODIR2 of P0 and Make FIODIR2[22]=1 
//-------------------------------------------------------------------------------------------------------------------
#include <LPC17xx.H>
void delay(unsigned long int dk);
unsigned long int di=0;
unsigned short int adc=0;
int main()
{
SystemInit();
LPC_SC->PCONP|=0X00001000; // PCON[12] is set as 1 and retains the Inititial Value
LPC_GPIO0->FIOMASK2|=0XBF; // P0.22is enabled where Relay is connected through a driver
LPC_GPIO0->FIODIR2|=0X40; // p0.22 is made as output pin
LPC_PINCON->PINSEL3|=0XC0000000; //Configure P1.31 as AD0.5 by choosing 3rd alternate function of P1.31
LPC_ADC->ADCR=0X00210320; // ADCR= 0000 0000 001(PDN)0 0001(BURST) 0000 0011(CLKDIV) 001(AIN.5)0 0000
while(1) 		  // Super Loop
{                         // Super Loop open
while((LPC_ADC->ADSTAT & 0X00000020)!=0X00000020) //Check Done5 of ADSTAT, If Done5=0 wait by executing while statement else exit
{
}
adc=((LPC_ADC->ADDR5>>4)& 0x00000fff); // Read the Converted Data from ADDR5[15:4] and Shifted Right to Shift the Position and ANDed with 0x00000FFF to MASK remaining bits

	if (adc > 0x9B2) // Comparing MV with RV
	{
		LPC_GPIO0->FIOSET2=0X40;  // If MV>RV energize the Relay by making P0.22=1(HIGH)
	}
	else 
	{
		LPC_GPIO0->FIOCLR2=0X40; // // If MV<=RV De-energize the Relay by making P0.22=0(LOW)
	}
}
}		// Super Loop Close
