#include <msp430.h>

int main(void)
{
    WDTCTL  = WDTPW | WDTHOLD;              // wizard words
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;

    P1DIR = BIT6;                           // BIT6 alternate output
    P1SEL = BIT6|BIT4;                      // BIT4 analog input (channel 4)

    TA0CTL   = TASSEL_2 | MC_1 | ID_3;      // use TA0.1 for PWM on P1.6
    TA0CCR0  = 0x3FF;                       // 10-bit maximum value
    TA0CCR1  = 0;                           // start off
    TA0CCTL1 = OUTMOD_7;                    // reset/set output mode

    ADC10CTL1 = INCH_4 | ADC10DIV_3;        // ADC10 channel 4, clock divider 3
    ADC10CTL0 = SREF_0 | ADC10SHT_3 |       // VCC/VSS ref, 64 x ADC10CLKs
               ADC10ON | ADC10IE;           // ADC10 enable, ADC10 interrupt enable
    ADC10AE0  = BIT4;                       // analog enable channel 4

    // __enable_interrupt();                // interrupts enabled
    while(1)
    {
        __delay_cycles(10000);              // wait for ADC ref to settle
        ADC10CTL0 |= ENC + ADC10SC;         // sampling and conversion start
        __bis_SR_register(CPUOFF | GIE);    // go to sleep with interrupts enabled
        TA0CCR1 = ADC10MEM & 0x3F8;         // assigns the value held in ADC10MEM to the TA0CCR1 register
    }

    return 0;
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
    __bic_SR_register_on_exit(CPUOFF);      // wake up
}
