#ifdef LINKTIME

#include <stdio.h>


int n=0, m=0;

void* __realmalloc(size_t size);
void __real_free(void *ptr);


void *__wrap_malloc(size_t size)
{
void *ptr=__real_malloc(size);
printf("malloc(%d)=%p\n", (int)size, ptr);
n++;

return ptr;
}


void __wrap_free(void *ptr)
{
__real_free(ptr);
printf("free(%p) \n" , ptr);
m++;
}


void check()
{

   if(m==n)
   {
     printf("There is no any memory leak! \n");
   }
   if(n>m) 
   {
     printf("We have memory leak ! \n");
   }
   else ("ERROR!!! \n" );
}


#endif
