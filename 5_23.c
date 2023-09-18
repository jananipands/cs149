#include <stdio.h>

int main(void) {
   const int NUM_INTS = 20;
   int arr[NUM_INTS];
   int left;
   int right;
   int count;

   scanf("%d", &count);
   for(int i = 0; i < count; i++){
      scanf("%d", &(arr[i]));
   }
   
   scanf("\n%d", &left);
   scanf("%d", &right);
   
   for(int i = 0; i < count; i++){
      if((arr[i] >= left) && (arr[i] <= right)){
         printf("%d,", arr[i]);
      }
   }
   
   printf("\n");

   return 0;
}
