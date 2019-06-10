#ifdef COMPILETIME
#include <stdio.h>
#include <malloc.h>

int n=0, m=0;


void *mymalloc(size_t size)
{
     void *ptr=malloc(size);
     printf("malloc(%d)=%p\n", (int)size, ptr);
     n++;
     return ptr;

}


void myfree(void *ptr)
{
     free(ptr);
     printf("free(%p)\n", ptr);
     m++;
}


void check()
{

   if(m==n)
   {
     printf("There is no any memory leak\n");
   }

   if(n>m) 
   {
   printf("you have  memory leak\n");
   }
   else ("ERROR !!! \n" );
}


#endif
