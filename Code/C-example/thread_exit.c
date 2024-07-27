#include <stdio.h>
#include <unistd.h>	// for sleep()
#include <pthread.h>

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    printf("Thread %d started.\n", thread_id);
    printf("Counting begins: ");
    for(int i = 10; i > 0; i--)
    {
	printf("%d ", i);
	sleep(1);
    }
    printf("Thread %d finished.\n", thread_id);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;
    int id1 = 1, id2 = 2;

    pthread_create(&thread1, NULL, thread_function, (void*)&id1);
    pthread_create(&thread2, NULL, thread_function, (void*)&id2);

    // Wait for the threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Main thread exiting.\n");
    pthread_exit(NULL);
}
