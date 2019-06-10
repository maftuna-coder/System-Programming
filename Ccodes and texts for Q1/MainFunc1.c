#include<string.h>
#include<math.h>
#include <stdio.h>
#include <stdlib.h>
#include<dlfcn.h>

  /*we reverse space via malloc function  */
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


   /* malloc built free spaces */  
  void myFree(int **matrix, int n)
{
	for(int i = 0; i < n; i++)
        {
   	    free(matrix[i]);
        }
 	free(matrix);
}


  /* Building matrix through malloc */
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
    

  /*We write new matrix into file here :) */
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
    void *handle;

    void (*matadd)(int**, int**, int**, int);
    void (*matsub)(int**, int**, int**, int);
    void (*matmult)(int**, int**, int**, int);
    void (*mattrans)(int**, int**, int);

    char* error;
    handle = dlopen("./libmatrix.so", RTLD_LAZY);

    if(!handle)
    {
      fprintf(stderr, "%s\n", dlerror());
      exit(1);
    }

    matadd = dlsym(handle, "matadd");
    if((error = dlerror())!=NULL)
    {
      fprintf(stderr, "%s\n", error);
      exit(1);
    }

    matsub = dlsym(handle, "matsub");
    if((error = dlerror())!=NULL)
    {
      fprintf(stderr, "%s\n", error);
      exit(1);
    }
   
    matmult = dlsym(handle, "matmult");
    if((error = dlerror())!=NULL)
    {
      fprintf(stderr, "%s\n", error);
      exit(1);
    }

    mattrans = dlsym(handle, "mattrans");
    if((error = dlerror())!=NULL)
    {
      fprintf(stderr, "%s\n", error);
      exit(1);
    }

    int** x = readMatrix("MATRIX2X2.txt", &n);
    int** y = readMatrix("MATRIX2X2B.txt", &n);
  
   int** z = createMatrix(n);
    matadd(x,y,z,n);
    writeMatrix("addMat2x2.txt", z, n);
    myFree(z, n);

    z = createMatrix(n);
    matsub(x,y,z,n);
    writeMatrix("subMat2x2.txt", z, n);
    myFree(z, n);

    z = createMatrix(n);
    matmult(x,y,z,n);
    writeMatrix("multMat2x2.txt", z, n);
    myFree(z, n);

    z = createMatrix(n);
    mattrans(y,z,n);
    writeMatrix("transposeMat2x2.txt", z, n);
    myFree(z, n);

    myFree(x, n);
    myFree(y, n);
    
    printf("Action completed!!!\n");

    if(dlclose(handle)<0){
       fprintf(stderr, "%s\n", dlerror());
       exit(1);
    }
   return 0;
  }

