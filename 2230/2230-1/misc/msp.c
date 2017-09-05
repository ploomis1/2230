#include <msp430.h>
#include <libemb/serial/serial.h>
#include <libemb/conio/conio.h>

int main(void)
{
    WDTCTL  = WDTPW | WDTHOLD;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;

    P1DIR |= 0b01000001; // direction output for P1.0 and P1.6
    P1OUT |= 0b01000001; // set P1.0 and P1.6 ON

    serial_init(9600);

    // while(1) {
    for(;;) {
        char cmd_line[90] = {0};
        cio_print((char *) "I'm waiting for a character!\n\r");
        char c = cio_getc();
        cio_printc(c);
        cio_print((char *) "\n\r");

        int ans=c%2;
        if(ans==1){
          int i;
  for( i = 0; i < 4; i++) {
      P1OUT ^= 0b00000001; // toggle both LEDs
      // P1OUT = P1OUT ^ 0b01000001;
      __delay_cycles(100000);
  }
        }
        else{
          int i;
  for( i = 0; i < 4; i++) {
      P1OUT ^= 0b01000000; // toggle both LEDs
      // P1OUT = P1OUT ^ 0b01000001;
      __delay_cycles(100000);
  }
        }

    }

    return 0;
}
