#include <msp430.h>
unsigned int color = 1;
int counter = 0;
char intensity = 2;
int direction =1;

int a = BIT7;
int b = BIT6;
int c = BIT2;
int d = BIT4;
int e = BIT1; //e is blue
int f = BIT5; //f is green
int g = BIT3;
int main(void)
{
   WDTCTL  = WDTPW | WDTHOLD;              // wizard words
   BCSCTL1 = CALBC1_1MHZ;
   DCOCTL  = CALDCO_1MHZ;
   #pragma vector=ADC10_VECTOR
 __interrupt void ADC10_ISR (void)
   {
      __bic_SR_register_on_exit(CPUOFF);      // wake up
   }
 }
