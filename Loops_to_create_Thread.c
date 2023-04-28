#include <stdio.h> //Header file for input and output
#include <unistd.h>//Header file that provides access to the POSIX operating system API.
#include <pthread.h> //Header file for pthread

pthread_mutex_t mutex;/*pthread_mutex_t is a data type in the POSIX threads library that represents a mutex, or mutual exclusion object. A mutex is a synchronization mechanism that is used to protect shared resources from concurrent access by multiple threads.*/
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
    pthread_exit(NULL); // Here NULL passing because returning nothing
}

int main()
{
    pthread_t th[4]; //Thread declaration of type pthread_t
    pthread_mutex_init(&mutex,NULL); //function call that initializes a mutex object referenced by the mutex variable using default attributes.
    printf("-->> Before thread\n");
    // I am putting it into if condition beacuse sometimes it may be possible that
    // resources are not available to create thread
    int i;
    for(i = 0; i < 4; i++)
    {
        if(pthread_create(&th[i],NULL,&sum,NULL) != 0)// Creating thread1
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