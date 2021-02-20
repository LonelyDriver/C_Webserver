target_sources(socket_example 
PRIVATE
 error_handling.c
 socketo_linux.c)

target_sources(thread_example
    PRIVATE
    threads/thread_linux.c)

target_sources(web_serv_example
    PRIVATE
    web_serv.c
    error_handling.c
    socketo_linux.c
    threads/thread_linux.c)

## tests

# unit tests

