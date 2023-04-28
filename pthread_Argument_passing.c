#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
int prime[10] = {2,3,5,7,11,13,17,19,23,29};
void* routine(void *arg)
{
    int index = *(int *)arg;
    int sum = 0;
    //printf("%d",prime[index]);
    for(int i = 0; i < 5; i++)
    {
        sum+= prime[index + i];
    }
    printf("Local sum-->> %d\n",sum);
    *(int *)arg = sum;
    return arg;
    //free(arg);
}

int main()
{
    pthread_t th[2];
    int i;
    for(i = 0; i < 2; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i * 5;
        if(pthread_create(&th[i],NULL,&routine,a) != 0)
        {
            perror("Failed to create thread\n");
        }
    }
    int globalSum = 0;
    for(i = 0; i < 2; i++)
    {
        int* result;

        if(pthread_join(th[i],(void **) &result) != 0)
        {
            return 1;
        }
        globalSum+= *result;
        free(result);
    }
    printf("Global sum is-->> %d\n",globalSum);
}