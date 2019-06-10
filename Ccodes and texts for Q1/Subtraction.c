
#include<stdio.h>

 void  matsub(int **x, int **y, int **z, int n)
 {
  for(int i = 0; i < n; i++)
  {
     for(int j = 0; j < n; j++)
     {
        z[i][j] = x[i][j] - y[i][j];
     }
        
   }
 }
