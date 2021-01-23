#include "socketo_linux.h"
#include "error_handling.h"

/**
 * @brief   https://man7.org/linux/man-pages/man2/socket.2.html
 *          AF_INET = IPv4
 *          TYPE = SOCK_STREAM (Provides sequenced, reliable, two-way, connection-based
                                byte streams.)
 * 
 * @param af 
 * @param type 
 * @param protocol 
 * @return socket_t 
 */

socket_t Create_Socket(int af, int type, int protocol) {
    socket_t sock;
    int ret;
    const int y=1;
    sock = socket(af, type, protocol);
    if(sock < 0){
        printf("Could not initialize socket: %d\n",sock); 
    }
    // socket options https://linux.die.net/man/3/setsockopt
    // clients share same port
    if((ret = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &y, sizeof(int))) != 0) {
        printf("Set socket options failed: %d\n", ret);
    }
    return sock;
}

err_t Connect(socket_t* sock, const char* ip, int port) {
    err_t err = {OK, GetErrorMessage(OK), 0};
    struct sockaddr_in server;
    struct hostent* host_info;
    unsigned long addr;

    if(ip == NULL || port < 0){
        err.error_nb = IP_PORT_INVALID;    
        err.error_msg = GetErrorMessage(err.error_nb);
        return err;
    }

    memset(&server, 0, sizeof(server));
    if((addr=inet_addr(ip)) != INADDR_NONE) {
        // converts the Internet host address from IPv4 numbers-and-dots notation into binary data in network byte order.
        memcpy((char*) &server.sin_addr, &addr, sizeof(addr));
    }else {
        // convert "localhost" to IPv4 address
        host_info = gethostbyname(ip);
        if(NULL == host_info) {
            err.error_nb = SERVER_INVALID;
            err.error_msg = GetErrorMessage(err.error_nb);
            return err;
        }
        memcpy((char*) &server.sin_addr, host_info->h_addr_list[0], host_info->h_length);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if((err.error_spec=connect(*sock, (struct sockaddr*) &server, sizeof(server))) < 0) {
        err.error_nb = COULD_NOT_CONNECT_TO_SERVER;
        err.error_msg = GetErrorMessage(err.error_nb);
    }
    return err;
}

err_t Send_Tcp(socket_t* sock, const char* buffer, size_t size) {
    err_t err = {OK, GetErrorMessage(OK), 0};
    int sent=0;
    int to_sent = size;
    int trys = 0;

    if(*sock < 0) {
        err.error_nb = SOCKET_INVALID;
        err.error_msg = GetErrorMessage(err.error_nb);
        return err;
    }

    while(to_sent > 0 || trys > 6){
        sent = send(*sock, buffer, size, 0);
        if(sent<0){
            err.error_nb = ERROR_WHILE_SENDING;
            err.error_msg = GetErrorMessage(err.error_nb);
            err.error_spec = sent;
            return err;
        }
        to_sent -= sent;
        trys++;
    }
    if(to_sent > 0){
        err.error_nb = COULD_NOT_SEND_ALL_DATA;
        err.error_msg = GetErrorMessage(err.error_nb);
        err.error_spec = to_sent;
    }
    return err;
}

unsigned int Receive_Tcp(socket_t* sock, char* buffer, size_t size) {
    unsigned int received = 0;

    if(*sock < 0) {
        printf("%s\n",GetErrorMessage(SOCKET_INVALID));
        return -1;
    }

    received = recv(*sock, buffer, size, 0);
    return received;
}

err_t Close(socket_t* sock) {
    err_t err = {OK, GetErrorMessage(OK), 0};

    if(*sock < 0){
        err.error_nb = SOCKET_INVALID;
        err.error_msg = GetErrorMessage(err.error_nb);
        return err;
    }

    if((err.error_spec= close(*sock)) < 0){
        err.error_nb = CLOSING_SOCKET_FAILED;
        err.error_msg = GetErrorMessage(err.error_nb);
    }
    return err;
}

err_t Bind(socket_t* sock, unsigned long address, unsigned short port) {
    err_t err = {OK, GetErrorMessage(OK), 0};
    struct sockaddr_in server;

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(address);
    server.sin_port = htons(port);

    printf("Listen on port: %d\n", port);
    if((err.error_spec=bind(*sock, (struct sockaddr*)&server, sizeof(server))) < 0) {
        err.error_nb = COULD_NOT_BIND_SOCKET;
        err.error_msg = GetErrorMessage(err.error_nb);
    }
    return err;
}

err_t Listen(socket_t* sock) {
    err_t err = {OK, GetErrorMessage(OK), 0};
    if((err.error_spec=listen(*sock, 5)) == -1) {
        err.error_nb = COULD_NOT_LISTEN_SOCKET;
        err.error_msg = GetErrorMessage(err.error_nb);
    }
    return err;
}

err_t Accept(socket_t* sock, socket_t* new_socket) {
    err_t err = {OK, GetErrorMessage(OK), 0};
    struct sockaddr_in client;
    unsigned int len;

    len = sizeof(client);
    *new_socket = accept(*sock, (struct sockaddr*)&client, &len);
    if(*new_socket == -1) {
        err.error_nb = ACCEPT_SOCKET_FAILED;
        err.error_msg = GetErrorMessage(err.error_nb);
    }
    printf("Connected to client with address: %s\n", inet_ntoa(client.sin_addr));
    return err;
}