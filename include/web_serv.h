#ifndef _WEBSERV_H
#define _WEBSERV_H
#include "error_handling.h"

typedef enum _http_methode_t {
    GET,
    POST
} http_methode_t;

typedef enum _HTTP_STATUS {
    OK_STATUS = 200,
    BAD_STATUS = 400
} HTTP_STATUS;

typedef enum _HTTP_CONTENTTYPE {
    APPLICATION_JSON = 0,
    APPLICATION_XML,
    TEXT_HTML,
    TEXT_PLAIN,
    TEXT_XML
} HTTP_CONTENTTYPE;

typedef struct _http_response_t {
    const char* payload;
    unsigned int payload_length;
    HTTP_CONTENTTYPE mime_type;
    HTTP_STATUS status;
} http_response_t;

typedef struct _http_request_t {
    const char* payload;
    unsigned int payload_length;
} http_request_t;

typedef void*  http_web_server_t;

typedef struct _http_server_config_t {
    unsigned int port;
    unsigned int connections;

} http_server_config_t;

typedef struct _http_uri_handler {
    const char* uri;
    http_methode_t methode;
    http_response_t (*handler)(const http_request_t* request);
} http_uri_handler;

err_t create_webserver(http_web_server_t* server, http_server_config_t* config);
http_server_config_t* make_server_config(unsigned int port, unsigned int connections);
void delete_server_config(http_server_config_t* config);
void delete_webserver(http_web_server_t* server);

err_t start_webserver(http_web_server_t server);

#endif // _WEBSERV_H