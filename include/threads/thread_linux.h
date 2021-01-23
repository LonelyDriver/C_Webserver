#ifndef _THREAD_LINUX_H
#define _THREAD_LINUX_H
#include <pthread.h>

#define thread_t    pthread_t

typedef void* (*thread_process)(void*);
#define thread_function     void*
#define thread_args         void*


#endif // _THREAD_LINUX_H