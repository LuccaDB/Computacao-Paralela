//Lucca Dias Bartholomei - 31910017
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define n 100000

double sum = 0.0;
int thread_count;

void *thread_sum(void* rank);

int main(int argc, char* argv[]){
    long thread;
    double pi;
    
    pthread_t* thread_handles;
    thread_count = strtol(argv[1],NULL,10);
    
    thread_handles = malloc(thread_count * sizeof(pthread_t));
    for(thread=0;thread<thread_count;thread++){
        pthread_create(&thread_handles[thread],NULL,thread_sum,(void*) thread);
    }
    
    printf("Heloo from main thread");
    
    for(thread=0;thread<thread_count;thread++){
        pthread_join(thread_handles[thread],NULL);
    }
    
    pi = 4*sum;
    
    printf("N: %d Pi: %f\n",n,pi);
    
    free(thread_handles);
    
    return 0;
}

void* thread_sum(void* rank){
    long my_rank = (long) rank;
    double factor;
    long long i;
    long long my_n = n/thread_count;
    long long my_first_i = my_n * my_rank;
    long long my_last_i = my_first_i + my_n;
    
    if(my_first_i % 2 == 0){
        factor = 1.0;
    }
    else{
        factor = -1.0;
    }
    
    for(i=my_first_i; i<my_last_i; i++, factor = -factor){
        sum += factor/(2*i + 1);
    }
    
    return NULL;
}
    
