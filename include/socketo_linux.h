#ifndef _SOCKETO_LINUX_H
#define _SOCKETO_LINUX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#define socket_t    int

#ifndef _SOCKETO_H
#define _SOCKETO_H

typedef struct socket_err_ {
    int error_nb;
    const char* error_msg;
    int error_spec;
} socket_err;

socket_t Create_Socket(int af, int type, int protocol);
socket_err Connect(socket_t* sock, const char* ip, int port);
socket_err Send_Tcp(socket_t* sock, const char* buffer, size_t size);
socket_err Receive_Tcp(socket_t* sock, char* buffer, size_t size);
socket_err Close(socket_t* sock);
socket_err Bind(socket_t* sock, unsigned long address, unsigned short port);
socket_err Listen(socket_t* sock);
socket_err Accept(socket_t* sock, socket_t* new_socket);


#endif // _SOCKETO_H


#endif // _SOCKETO_WRAP_H