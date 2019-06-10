
#include<string.h>
#include<math.h>
#include <stdio.h>
#include <stdlib.h>
#include<dlfcn.h>


  /* we reverse space through malloc function */
  int **readMatrix( char* fileName, int* n)
  {
	FILE* file_ptr = fopen(fileName, "r");
 	fscanf(file_ptr, "%d", n);
	int **result = (int**)malloc(*n*sizeof(int*));

	for(int i = 0; i < *n; i++)
        {
	   result[i] = (int*)malloc(*n*sizeof(int));
	   for(int j = 0; j <*n; j++)
           {
 	      fscanf(file_ptr, "%d", &result[i][j]);	
	   }
	}
	fclose(file_ptr);
	return result;
  }


  /* yousee here free space what we did by malloc function */ 
  void myFree(int **matrix, int n)
  {
	for(int i = 0; i < n; i++)
        {
   	    free(matrix[i]);
        }
 	free(matrix);
  }

  /* i build matrix via malloc function */
  int **createMatrix(int n)
  {    
	int **result = (int**)malloc(n*sizeof(int*));

	for(int i = 0; i < n; i++)
        {
   	    result[i] = (int*)malloc(n*sizeof(int));
	    for(int j = 0; j < n; j++)
            {
	       result[i][j] = 0;
	    }
 	}
   return result;
  }
   
 /* we write new matrix into file */
  void writeMatrix(char *fileName, int**z, int n)
{
    FILE *file_ptr = fopen(fileName, "w");

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
            fprintf(file_ptr, "%d ", z[i][j]);
        fprintf(file_ptr, "\n");
    }
    fclose(file_ptr);
}

  void  matadd(int **x, int **y, int **z, int n);
  void  matsub(int **x, int **y, int **z, int n);
  void  matmult(int **x, int **y, int **z, int n);
  void  mattrans(int **y, int **z, int n);

  int main()
  {
    int n = 0;

    int** x = readMatrix("MATRIX2X2.txt", &n);
    int** y = readMatrix("MATRIX2X2B.txt", &n);
  
    int** z = createMatrix(n);
    matadd(x,y,z,n);
    writeMatrix("addMATRIX2X2.txt", z, n);
    myFree(z, n);
          
    z = createMatrix(n);
    matsub(x,y,z,n);
    writeMatrix("subMATRIX2X2.txt", z, n);
    myFree(z, n);

    z = createMatrix(n);
    matmult(x,y,z,n);
    writeMatrix("multMATRIX2X2.txt", z, n);
    myFree(z, n);

    z = createMatrix(n);
    mattrans(y,z,n);
    writeMatrix("transMATRIX2X2.txt", z, n);
    myFree(z, n);

    myFree(x, n);
    myFree(y, n);
    

 printf("Well done! Complete :) \n");
  }

