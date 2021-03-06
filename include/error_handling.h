#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

typedef enum ERRR_ {
    OK_ERROR=0,
    CREATE_SOCKET_FAILED,
    IP_PORT_INVALID,
    SERVER_INVALID,
    COULD_NOT_CONNECT_TO_SERVER,
    BUFFER_INVALID,
    ERROR_WHILE_SENDING,
    COULD_NOT_SEND_ALL_DATA,
    SOCKET_INVALID,
    RECEIVING_FAILED,
    CLOSING_SOCKET_FAILED,
    COULD_NOT_BIND_SOCKET,
    COULD_NOT_LISTEN_SOCKET,
    ACCEPT_SOCKET_FAILED,
    OUT_OF_MEMORY,
    INVALID_SERVER_HANDLE,
    COULD_NOT_CREATE_SERVER_THREAD,
    INVALID_THREAD_INFO
} ERRR;

typedef struct _err_ {
    int error_nb;
    const char* error_msg;
    int error_spec;
} err_t;

const char* GetErrorMessage(ERRR error);

#endif