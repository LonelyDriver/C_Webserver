#include "thread_al.h"
#include <stdlib.h>

thread_info_t* make_thread_info(thread_process process, thread_args args) {
    thread_info_t* t_info = malloc(sizeof(*t_info));
    t_info->process = process;
    t_info->args = args;

    return t_info;
}

void delete_thread_info(thread_info_t* thread_info) {
    free(thread_info);
}

int create_thread(thread_t* thread_id, thread_info_t* thread_info) {
    int rc = pthread_create(thread_id, NULL, thread_info->process, thread_info->args);
    return rc;
}
int join_thread(thread_t thread_id) {
    int rc = pthread_join(thread_id, NULL);
    return rc;
}