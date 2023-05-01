//This is the program to understand how to return variable in pthread

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

void* roll_dice()
{
    int value = (rand() % 6) + 1;
    int *result = malloc(sizeof(int));
    *result = value;
    //printf("Value = %d\n",value);
    return (void *) result;
}

int main()
{
    int *res;
    srand(time(NULL));
    pthread_t th1;
    if(pthread_create(&th1,NULL,&roll_dice,NULL) != 0)
    {
        return 1;
    }
    if(pthread_join(th1, (void **) &res) != 0)
    {
        return 2;
    }
    printf("Value = %d\n",*res);
    free(res);
}