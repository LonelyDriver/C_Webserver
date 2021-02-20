#ifndef _THREAD_AL_H
#define _THREAD_AL_H

#if __linux__
#include "thread_linux.h"
#else

#endif


typedef struct _thread_info_t {
    thread_process process;
    thread_args args;
} thread_info_t;

thread_info_t* make_thread_info(thread_process process, thread_args args);
void delete_thread_info(thread_info_t* thread_info);

int create_thread(thread_t* thread_id, thread_info_t* thread_info);
int join_thread(thread_t thread_id);
void thread_sleep(long time_ms);


#endif // _THREAD_AL_H
