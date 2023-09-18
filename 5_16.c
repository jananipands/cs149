#include <stdio.h>

int main(void) {
   const int NUM_ELEMENTS = 20;         // Number of input integers
   int userVals[NUM_ELEMENTS];          // Array to hold the user's input integers
   int count = 0;

   /* Type your code here. */
   int num = NUM_ELEMENTS - 1 - count;
   while((scanf("%d", &(userVals[num])) == 1)){
      count++;
      num = NUM_ELEMENTS - 1 - count;
   }
   
   for(int i = NUM_ELEMENTS - count; i < NUM_ELEMENTS - 1; ++i){
      printf("%d,", userVals[i]);
   }
   
   printf("\n");
   return 0;
}