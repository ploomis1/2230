#include <msp430.h>

#define period 1200;
#define duty 1200/ 100;

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
    WDTCTL  = WDTHOLD | WDTPW;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;

    P1DIR = 0xF1;
    P2DIR = 0xFF;
    P1OUT |= BIT5;
    P2OUT = 0x00;
    //P1DIR = BIT0 | BIT6;
    //P1OUT = BIT0 | BIT3;

    P1DIR = 0b11111111;//BIT6|BIT2;                        // P1.6 as output
    P1SEL = 0b11111111;//BIT6|BIT2;       // P1.6 alternate mode
    P2SEL   &= ~(BIT6 | BIT7);                      // P2.6 and P2.7 as Outputs
    P2OUT = 3;
    //unsigned int timeperiod;
    TA0CTL   = TASSEL_2 | MC_1 | ID_3;
    TA0CCR0 = period;                        //Setting the period to the counter0.

    TA0CCR1 = intensity + duty;              //Setting the counter1 to the intensity and duty.
    TA0CCTL0 = CCIE;
    TA0CCTL1 = OUTMOD_4;                     // enable CCR0 to interrupt

    P1DIR |= a;								// Set P2.0 to output direction
  	P1DIR |= b;								// Set P2.1 to output direction
  	P1DIR |= c;								// Set P2.2 to output direction
  	P1DIR |= d;								// Set P2.3 to output direction
  	P1DIR |= e;								// Set P2.4 to output direction
  	P1DIR |= f;								// Set P2.5 to output direction
  	P1DIR |= g;

    __enable_interrupt();                             // enable the interrupt
    LPM0;// go to sleep

  //  for (int timeperiod=0; timeperiod<20; timeperiod++)//for loop for the timeperiod of the light to be on
  //  {
              P1OUT |= b; //this is 22, just a a is 2
              //P2OUT = g;
              //P2OUT = e; //blue or 2
              //P2OUT = f; green

              //delay();
              //P2OUT &= ~(a + b + c + d + e + f); //this turns everything off
              __interrupt;
  //  }

    return 0;
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer0_A1_ISR(void)       // interrupt
{

}

//#pragma vector = TIMER0_A1_VECTOR
//__interrupt void TIMER0_A1_VECTOR(void)
//{
  //  __delay_cycles(32000);
//}
