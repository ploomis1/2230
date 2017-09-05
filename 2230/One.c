#include <stdio.h>
#include <stdlib.h>


int i = 0;
int digit;
char * Table = "0123456789ABCDEF";
 int main(int argc, char *argv[]){
   int value = atoi(argv[1]);
   int base = atoi(argv[2]);
  // char Table[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
   while(value != 0){
     digit = value % base;
     value = value/base;
     if((i == 0) && (digit <= 9)){
     printf("%d %d \n", value, digit);
     i++;
   }
 }
 if(digit > 9){
 printf("%d %c \n", value, Table[digit]);
 }
}
