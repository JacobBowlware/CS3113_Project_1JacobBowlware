// Author:     Jacob Bowlware
// VM Address: cs014@cs014.cs.ourcloud.ou.edu
// OU 4x4:     bowl0047
// OUID:       113536730

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

/* Key number */
#define SHMKEY ((key_t)1497)

typedef struct
{
    int value;
} shared_mem;

shared_mem *total;

void process1()
{
    for (int i = 0; i < 100000; i++)
    {
        total->value++;
    }
    printf("From Process 1: counter = %d\n", total->value);
    exit(0);
}

void process2()
{
    for (int i = 0; i < 100000; i++)
    {
        total->value++;
    }
    printf("From Process 2: counter = %d\n", total->value);
    exit(0);
}

void process3()
{
    for (int i = 0; i < 100000; i++)
    {
        total->value++;
    }
    printf("From Process 3: counter = %d\n", total->value);
    exit(0);
}

void process4()
{
    for (int i = 0; i < 300000; i++)
    {
        total->value++;
    }
    printf("From Process 4: counter = %d\n", total->value);
    exit(0);
}

int main()
{
    int shmid, pid1, pid2, pid3, pid4, status;
    char *shmadd = (char *)0;

    /* Create and connect to a shared memory segment */
    if ((shmid = shmget(SHMKEY, sizeof(shared_mem), IPC_CREAT | 0666)) < 0)
    {
        perror("shmget");
        exit(1);
    }

    if ((total = (shared_mem *)shmat(shmid, shmadd, 0)) == (shared_mem *)-1)
    {
        perror("shmat");
        exit(0);
    }

    /* Initialize shared memory to 0 */
    total->value = 0;

    /* Create child processes */
    if ((pid1 = fork()) == 0)
        process1();
    if ((pid2 = fork()) == 0)
        process2();
    if ((pid3 = fork()) == 0)
        process3();
    if ((pid4 = fork()) == 0)
        process4();

    /* Parent waits for all children to finish */
    waitpid(pid1, &status, 0);
    printf("Child with PID %d has just exited.\n", pid1);

    waitpid(pid2, &status, 0);
    printf("Child with PID %d has just exited.\n", pid2);

    waitpid(pid3, &status, 0);
    printf("Child with PID %d has just exited.\n", pid3);

    waitpid(pid4, &status, 0);
    printf("Child with PID %d has just exited.\n", pid4);

    /* Detach and remove shared memory */
    if (shmdt(total) == -1)
    {
        perror("shmdt");
        exit(-1);
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("shmctl");
        exit(-1);
    }

    printf("End of Program.\n");

    return 0;
}
