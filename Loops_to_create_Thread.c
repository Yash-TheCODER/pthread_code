#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;
int mails =0;
void *sum()
{
    for(int i = 0; i < 100; i++)  // Here Race condition occurs when we use 1000000 in place of 100 
    {//bcoz th2 started working in betweeen parallely -->> To solve it we use mutex lock
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
        // read mails 
        // increment
        // write mails
    }
    return NULL;
}

int main()
{
    pthread_t th[4]; //Thread declaration of type pthread_t
    pthread_mutex_init(&mutex,NULL);
    printf("-->> Before thread\n");
    // I am putting it into if condition beacuse sometimes it may be possible that
    // resources are not available to create thread
    int i;
    for(i = 0; i < 4; i++)
    {
        if(pthread_create(&th[i],NULL,sum,NULL) != 0)// Creating thread1
        {
            perror("Failed to create thread\n");
            return 1;
        }
        printf("Thread %d has started\n",i);
        
    }
    for(i = 0; i < 4; i++)
    {
        if(pthread_join(th[i],NULL) != 0)// Here the process will wait for thread to finish
        {
            return 2;
        }
        printf("Thread %d has finished execution\n",i);
    }
    pthread_mutex_destroy(&mutex);
    printf("Value of x is -->> %d\n",mails);
    printf("Thread creation  completed\n");
    
}