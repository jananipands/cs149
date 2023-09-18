#include <stdio.h>

int main(void) {
   const int NUM_ELEMENTS = 9;
   int userValues[NUM_ELEMENTS];    // Set of data specified by the user
   int input = 1;
   int val = 0;
   
   while((input == 1) && ((val - 1) <= 9)){
      scanf("%d", &(userValues[val]));
      if(userValues[val] == -1){
         input = 0;
      }
      ++val;
   }
   
   if(val > 10){
      printf("Too many numbers\n");
      return 0;
   }
   
   int middle = val / 2 - 1;
   
   printf("Middle item: %d\n", userValues[middle]);

   return 0;
}
