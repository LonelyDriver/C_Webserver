#ifndef _WEBSERV_H
#define _WEBSERV_H
#include "error_handling.h"

typedef enum _HTTP_STATUS {
    OK = 200,
    BAD = 400
} HTTP_STATUS;

typedef enum _HTTP_CONTENTTYPE {
    APPLICATION_JSON = 0,
    APPLICATION_XML,
    TEXT_HTML,
    TEXT_PLAIN,
    TEXT_XML
} HTTP_CONTENTTYPE;

typedef struct _http_response {
    const char* payload;
    unsigned int payload_length;
    HTTP_CONTENTTYPE mime_type;
    HTTP_STATUS status;
} http_response;

typedef struct _http_request {
    const char* payload;
    unsigned int payload_length;
} http_request;

typedef struct _http_web_server_t {

} http_web_server_t;

typedef struct _http_server_config_t {
    unsigned int port;
    unsigned int connections;

} http_server_config_t;

err_t Create_Webserver(http_web_server_t* server, http_server_config_t* config);
http_server_config_t* make_server_config(unsigned int port, unsigned int connections);

#endif // _WEBSERV_H