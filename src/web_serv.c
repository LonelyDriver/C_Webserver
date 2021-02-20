#include "web_serv.h"
#include <stdlib.h>
#include <stdio.h>
#include "socketal.h"
#include "thread_al.h"

typedef struct _web_server_t {
    http_server_config_t* config_data;
    socket_t listen_sock;
    thread_t entry_point;
    socket_t* socks;
    thread_t* threads;

} web_server_t;

static err_t init_listening_socket(web_server_t* server);
static err_t start_session(web_server_t* server);
static thread_function server_entry_point(thread_args args);
static err_t start_worker_thread(web_server_t* server, socket_t* sock,  int thread_index);
static thread_function worker_thread(thread_args args);


http_server_config_t* make_server_config(unsigned int port, unsigned int connections) {
    http_server_config_t* config = malloc(sizeof(*config));
    config->connections = 5;
    config->port = 5000;

    return config;
}

err_t create_webserver(http_web_server_t* server, http_server_config_t* config) {
    err_t err = {OK_ERROR, GetErrorMessage(OK_ERROR), 0};
    web_server_t* true_server = malloc(sizeof(*true_server));
    true_server->config_data = config;

    printf("Connections: %d\nPort%d\n", true_server->config_data->connections, true_server->config_data->port);

    if(true_server == NULL) {
        err.error_nb = OUT_OF_MEMORY;
        err.error_msg = GetErrorMessage(err.error_nb);
        return err;
    }

    true_server->socks = calloc(config->connections, sizeof(socket_t));
    true_server->threads = calloc(config->connections, sizeof(thread_t));
    if(&true_server->socks == NULL || &true_server->threads == NULL) {
        err.error_nb = OUT_OF_MEMORY;
        err.error_msg = GetErrorMessage(err.error_nb);
        return err;
    }

    printf("Reserved memory for %d sockets\n", config->connections);
    *server = true_server;

    return err;
}

err_t start_webserver(http_web_server_t server) {
    err_t err = {OK_ERROR, GetErrorMessage(OK_ERROR), 0};

    if(server == NULL) {
        err.error_nb = INVALID_SERVER_HANDLE;
        err.error_msg = GetErrorMessage(err.error_nb);
        return err;
    }
    web_server_t* true_server = server;

    printf("Connections: %d\nPort%d\n", true_server->config_data->connections, true_server->config_data->port);

    err = init_listening_socket(true_server);
    if(err.error_nb != OK_ERROR) {
        delete_webserver(true_server);
        return err;
    }
    printf("Starting session\n");
    start_session(true_server);

    return err;
}

static err_t init_listening_socket(web_server_t* server) {
    err_t err = {OK_ERROR, GetErrorMessage(OK_ERROR), 0};
    server->listen_sock = Create_Socket(AF_INET, SOCK_STREAM, 0);

    if(server->listen_sock == -1) {
        err.error_nb = CREATE_SOCKET_FAILED;
        err.error_msg = GetErrorMessage(err.error_nb);
        err.error_spec = errno;
        return err;
    }

    err = Bind(&server->listen_sock, INADDR_ANY, server->config_data->port);
    if(err.error_nb != OK_ERROR) {
        return err;
    }

    err = Listen(&server->listen_sock);
    return err;
}

static err_t start_session(web_server_t* server) {
    err_t err = {OK_ERROR, GetErrorMessage(OK_ERROR), 0};
    
    thread_info_t* thread_info = make_thread_info(server_entry_point, (web_server_t*)server);
    if(thread_info == NULL) {
        err.error_nb = INVALID_THREAD_INFO;
        err.error_msg = GetErrorMessage(err.error_nb);
        return err;
    }
    int rc = create_thread(&server->entry_point, thread_info);
    if(rc < 0) {
        err.error_nb = COULD_NOT_CREATE_SERVER_THREAD;
        err.error_msg = GetErrorMessage(err.error_nb);
        err.error_spec = rc;
    }
    return err;
}

static thread_function server_entry_point(thread_args args) {
    err_t err = {OK_ERROR, GetErrorMessage(OK_ERROR), 0};
    web_server_t* server = args;
    socket_t* new_sock;
    int i = 0;

    printf("Listening on port %d\n", server->config_data->port);
    printf("Connections: %d\n",server->config_data->connections);
    while(1) {
        new_sock = NULL;
        for(i=0;i<server->config_data->connections;i++) {
            //printf("Sockets:%d\n", server->socks[i]);
            if(server->socks[i] == 0) {
                new_sock = &server->socks[i];
                printf("Found free socket (%d)\n", i);
                break;
            }
        }
        if(new_sock == NULL) {
            printf("No free thread found\n");
            thread_sleep(10);
            continue;
        }
        printf("Accept for %d\n",i);
        err = Accept(&server->listen_sock, new_sock);
        if(err.error_nb != 0) {
            printf("ERROR: %s\n", err.error_msg);
            return;       
        }
        printf("Starting server thread\n");
        start_worker_thread(server, new_sock, i);
    }
}

static err_t start_worker_thread(web_server_t* server, socket_t* sock, int thread_index) {
    err_t err = {OK_ERROR, GetErrorMessage(OK_ERROR), 0};

    printf("make info\n");
    thread_info_t* thread_info = make_thread_info(worker_thread, (web_server_t*)server);
    thread_info->args = (socket_t*)sock;
    printf("create thread\n");
    int rc = create_thread(&server->threads[thread_index], thread_info);
}

static thread_function worker_thread(thread_args args) {
    err_t err = {OK_ERROR, GetErrorMessage(OK_ERROR), 0};
    char buf[0x0200];
    unsigned int recv_bytes = 0;
    socket_t* sock = (socket_t*)args;
    
    recv_bytes = Receive_Tcp(sock, buf, 0x0200);

    printf("Bytes received = %d\n", recv_bytes);
    printf("Bytes=%s\n", buf);
    

    Close(sock);
    *sock = 0;
}

void delete_server_config(http_server_config_t* config) {
    free(config);
    config = NULL;
}

void delete_webserver(http_web_server_t* server) {
    web_server_t* true_server = server;

    free(true_server->socks);
    free(true_server->threads);
    true_server->socks = NULL;
    true_server->threads = NULL;
    free(true_server);
    true_server = NULL;
}
