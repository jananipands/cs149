#include <stdio.h>

int main(void) {
   const int NUM_ELEMENTS = 20;
   int userValues[NUM_ELEMENTS];    // Set of data specified by the user
   int count;
   int limit;
   
   scanf("%d", &count);

   /* Type your code here. */
   for(int i = 0; i < count; i++){
      scanf("%d", &(userValues[i]));
   }
   
   scanf("%d", &limit);
   
   for(int i = 0; i < count; i++){
      if(userValues[i] <= limit){
         printf("%d,", userValues[i]);
      }
   }
   
   printf("\n");
      

   return 0;
}
