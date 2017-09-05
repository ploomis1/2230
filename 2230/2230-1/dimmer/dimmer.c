#include <msp430.h>
unsigned int color = 1;
int main(void)
{
   WDTCTL  = WDTPW | WDTHOLD;              // wizard words
   BCSCTL1 = CALBC1_1MHZ;
   DCOCTL  = CALDCO_1MHZ;

   P1DIR = BIT6 | ~(BIT3);
   P2DIR = BIT5 | BIT1; //when commented its red           // BIT6 alternate output
   P1REN |= BIT3;
   P2SEL = BIT5 | BIT1;
   P1SEL = BIT6;
   P1OUT |= BIT3;
   P1IE  |= BIT3;
   P1IES |= BIT3;
   P1IFG &= ~BIT3;

   TA0CTL   = TASSEL_2 | MC_1 | ID_3;      // use TA0.1 for PWM on P1.6
   TA0CCR0  = 0x3FF;                       // 10-bit maximum value
   TA0CCR1  = 0;                           // start off
   TA0CCTL0 = CCIE;
   TA0CCTL1 = OUTMOD_7;                    // reset/set output mode

   TA1CTL   = TASSEL_2 | MC_1 | ID_3;      // use TA1.1 for PWM on P1.6
   TA1CCR0  = 0x3FF;                       // 10-bit maximum value
   TA1CCR1  = 0;                           // start off
   TA1CCTL1 = OUTMOD_7;                    // reset/set output mode

   TA1CCR2  = 0x3FF;                       // 10-bit maximum value
   TA1CCTL2 = OUTMOD_7;                    // reset/set output mode

   ADC10CTL1 = INCH_4 | ADC10DIV_3;        // ADC10 channel 4, clock divider 3
   ADC10CTL0 = SREF_0 | ADC10SHT_3 |       // VCC/VSS ref, 64 x ADC10CLKs
              ADC10ON | ADC10IE;           // ADC10 enable, ADC10 interrupt enable
   ADC10AE0  = BIT4;                       // analog enable channel 4

    __enable_interrupt();                // interrupts enabled
   while(1)
   {
       __delay_cycles(10000);              // wait for ADC ref to settle
       ADC10CTL0 |= ENC + ADC10SC;         // sampling and conversion start
       //__bis_SR_register(CPUOFF | GIE);    // go to sleep with interrupts enabled
       //TA0CCR1 = ADC10MEM & 0x3F8;         // assigns the value held in ADC10MEM to the TA0CCR1 register
       if(color == 1){
           TA0CCR1 = ADC10MEM & 0x3F8;         // assigns the value held in ADC10MEM to the TA0CCR1 register
       }else if(color == 2){
           TA1CCR1 = ADC10MEM & 0x3F8;         // assigns the value held in ADC10MEM to the TA1CCR1 register
       }else if(color == 3){
           TA1CCR2 = ADC10MEM & 0x3F8;         // assigns the value held in ADC10MEM to the TA1CCR2 register
       }
   }

   return 0;
}
#pragma vector=PORT1_VECTOR
__interrupt void portinterrupt (void){
  P1IFG &= ~BIT3;//this wont let me switch without it bit4 is yello??
    if(color == 1){
      color = 2;
    }else if(color == 2){
      color = 3;
    }else if(color == 3){
      color = 1;
    }
}
// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
   __bic_SR_register_on_exit(CPUOFF);      // wake up
}
