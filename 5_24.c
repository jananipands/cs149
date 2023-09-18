#include <stdio.h>
#include <limits.h>

int main(void) {

   /* Type your code here. */
   const int NUM_INTS = 20;
   int arr[NUM_INTS];
   int min1 = INT_MAX;
   int min2 = INT_MAX;
   int minIndex = 0;
   
   int count;
   
   scanf("%d\n", &count);
   for(int i = 0; i < count; i++){
      scanf("%d", &(arr[i]));
   }
   
   for(int i = 0; i < count; i++){
      if(arr[i] < min1){
         min1 = arr[i];
         minIndex = i;
      }
   }
   
   for(int i = 0; i < count; i++){
      if((i != minIndex) && (arr[i] < min2)){
         min2 = arr[i];
      }
   }
   
   printf("%d and %d\n", min1, min2);
   
   
   
   
   

   return 0;
}
