#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    pid_t tid = syscall(SYS_gettid);
    printf("Thread ID: %d\n", tid);
    return 0;
}

