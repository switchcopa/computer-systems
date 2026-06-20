
/* 
	What is a thread in computer science? We're about to find out in this introduction.
	A thread is a small unit of execution within a process. We know that each process
	has its own virtual address space, and each cannot run multiple instructions at once, 
	by default. For example, let's say a big web server handles a lot of users at the same 
	time, and we have user number 1, trying to put in his password or share data with the 
	server. At the same time, there are other users trying to do the same thing, and the 
	server is listening/waiting for input. So do we have to wait until the first user 
	finishes and then we execute the next? What if he's asleep, then we would have to wait
	the whole day! And this is what problem threads solve, they're like multiple "workers"
	inside the same program, each executing a certain task, simultaneously.

	Each thread has its own: 
		-> Registers
		-> stack,
		-> and also the PC (the program counter)

	Let's import the POSIX Threads API, or "pthreads.h" in C.
*/

#include <stdio.h>
#include <pthread.h>

/*
        First of all, pthread_t is the opaque data type, its purpose is to refer to specific 
        threads with certain pthreads.h functions:

                pthread_t thread;
        
        Also, pthread_attr_t is also a opaque data type used to store thread attributes in the 
        pthreads library.

	Next, we're going to know how to create a thread using the pthreads API.
	The library function pthread_create allows us to do so:

                int pthread_create(
                        pthread_t *thread,
                        const pthread_attr_t *attr,
                        void *(*routine)(void *),
                        void *arg
                );

        Here: 
                -> thread parameter refers to the thread we want to execute.
                -> attr is the thread attributes, like stack size or detached state, etc...
                        We're only going to use NULL for it (it's the default).
                -> the third parameter is a pointer to a function that takes a void * and returns
                a void * (the thread result).
                -> The fourth argument is the argument we would like to pass to the function.
        
        Now that we know how to define and create a thread, what if we want to wait for a thread to finish then
        execute some piece of code?
        The function pthread_join allows us to do so:

                int pthread_join(
                        pthread_t thread,
                        void **retval
                );

        It basically waits for the thread to finish by calling the thread blocks until it's done,
        and optionally receives a return its return value (returned by routine).

        And we are done! Let's practice by first writing a thread function that we would like to execute,
        and execute two threads at once.
        We would also like to see the order of execution for each thread, because one can finish before the other
        due to OS scheduling.
*/

void *routine(void *arg) {
        int n = *(int*)arg; 
        printf("Hello from routine %d!\n", n);
        return NULL;
}

int main(void) {
        // our threads
        pthread_t t1, t2;
        // the number of the routine
        int n1 = 1, n2 = 2;
        // the return value we will get from routine
        void *ret; 

        // create the threads
        pthread_create(&t1, NULL, routine, &n1);
        pthread_create(&t2, NULL, routine, &n2);
        
        // wait till they finish
        pthread_join(t1, &ret);
        pthread_join(t2, &ret);
        
        return 0;
}
