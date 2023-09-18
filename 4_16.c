#include <stdio.h>

int main(void) {
   
   int curNum = 0;
   int max = 0;
   int count = 0;
   int sum = 0;

   while(scanf("%d", &curNum) == 1) {
      if (curNum >= 0) {
         sum += curNum;
         count++;
         if (max < curNum) {
            max = curNum;
         }
      }
   }
   
   float average = (float) sum / count;
   printf("%d %0.2lf\n", max, average);

   return 0;
}