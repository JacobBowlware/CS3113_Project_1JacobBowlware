CS3113
Project 1
Jacob Bowlware

# 1. Prerequisites
To compile and run the program, ensure the following:

    GCC (GNU Compiler Collection) is installed.
    The program is run on a Linux or UNIX-based system, preferably in the virtual machine provided for the CS-3113 course.
    Access to POSIX shared memory system calls (shmget(), shmat(), etc.).

If working on a different environment, ensure it supports the necessary system calls.

# 2. Execution Instructions
To compile and run the program, follow these steps:
* gcc shared_memory_increment.c -o shared_memory_increment
* ./shared_memory_increment


Program Output: The program will create four child processes. Each child process will increment the shared variable and print its final value. The parent process will print the process ID of each child as they exit and terminate the program.

A typical output should look like this:
    From Process 1: counter = 100000
    From Process 2: counter = 300000
    From Process 3: counter = 580000
    From Process 4: counter = 1080000
    Child with PID 91544 has just exited.
    Child with PID 91545 has just exited.
    Child with PID 91546 has just exited.
    Child with PID 91547 has just exited.
    End of Program.

