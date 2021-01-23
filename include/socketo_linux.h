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
#include "error_handling.h"

#define socket_t    int

socket_t Create_Socket(int af, int type, int protocol);
err_t Connect(socket_t* sock, const char* ip, int port);
err_t Send_Tcp(socket_t* sock, const char* buffer, size_t size);
unsigned int Receive_Tcp(socket_t* sock, char* buffer, size_t size);
err_t Close(socket_t* sock);
err_t Bind(socket_t* sock, unsigned long address, unsigned short port);
err_t Listen(socket_t* sock);
err_t Accept(socket_t* sock, socket_t* new_socket);

#endif // _SOCKETO_WRAP_H