#include "web_serv.h"
#include <stdlib.h>
#include <stdio.h>

http_server_config_t* make_server_config(unsigned int port, unsigned int connections) {
    http_server_config_t* config = malloc(sizeof(*config));
    config->connections = 5;
    config->port = 5000;

    return config;
}

err_t Create_Webserver(http_web_server_t* server, http_server_config_t* config) {
    err_t err = {OK, GetErrorMessage(OK), 0};
    server = malloc(sizeof(*server));
}
