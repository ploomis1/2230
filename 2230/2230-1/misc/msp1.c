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
    int blink=0;
    int j=0;
    // while(1) {
    for(;;) {
        char cmd_line[90] = {0};
        cio_print((char *) "I'm waiting for a character!\n\r");
        char c = cio_getc();
    while(c != '\r') {
     if(c == 0x08) {
       if(j != 0) {
         cmd_line[--j] = 0;
         cio_printc(0x08); cio_printc(' ');cio_printc(0x08);

       }
     } else {
       cmd_line[j++] = c; cio_printc(c);
     }
     c=c-'0';
     blink=(blink *10)+c;
     c = cio_getc();

   }

  //(6x535)
   cio_print((char *) "\n\n\r");

        int ans=blink%2;
        if(ans==1){
        cio_printf("%i is odd\n",blink);
          int i;
  for( i = 0; i < 4; i++) {
      P1OUT ^= 0b00000001; // toggle both LEDs
      // P1OUT = P1OUT ^ 0b01000001;
      __delay_cycles(100000);
  }
        }
        else{
          cio_printf("%i is even\n",blink);
          int i;
  for( i = 0; i < 4; i++) {
      P1OUT ^= 0b01000000; // toggle both LEDs
      // P1OUT = P1OUT ^ 0b01000001;
      __delay_cycles(100000);
  }
        }
 blink=0;
    }

    return 0;
}
