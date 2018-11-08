#include "stdlib.h"
#include "stdio.h"


int main()
{




cudaDeviceProp prop;

int count;

cudaGetDeviceCount(&count);

for(int i=0;i<count;i++)
{

cudaGetDeviceProperties(&prop,i);

printf("=======================================\n");
printf(" name= %s\n",prop.name);
printf(" compute cap= %d\n",prop.major);
printf(" GlobalMem = %d\n",prop.totalGlobalMem);
printf(" multi process count = %ld\n",prop.multiProcessorCount);
printf(" max thread/block = %d\n",prop.maxThreadsPerBlock);



}


}

                       
