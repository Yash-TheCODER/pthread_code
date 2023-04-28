// C program to create thread using pthread 
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>//Header file for pthread

void *sum()
{
    printf("Printing sum\n");
    sleep(2);// Apply sleep to see that both threads runs parallely or not
    printf("Printing sum endsss\n");
    return NULL;
}

int main()
{
    pthread_t th1,th2; //Thread declaration of type pthread_t
    printf("-->> Before thread\n");
    // I am putting it into if condition beacuse sometimes it may be possible that
    // resources are not available to create thread
    if(pthread_create(&th1,NULL,sum,NULL) != 0)// Creating thread1
    {
        return 1;
    }
    if(pthread_create(&th2,NULL,sum,NULL) != 0) // Creating thread2
    {
        return 2;
    }
    if(pthread_join(th1,NULL) != 0)// Here the process will wait for thread to finish
    {
        return 3;
    }
    if(pthread_join(th2,NULL)) // Here the process will wait for thread to finish
    {
        return 4;
    }
    
    printf("Thread creation  completed\n");
    
}