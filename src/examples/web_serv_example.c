#include <stdio.h>
#include "web_serv.h"


int main() {
    http_web_server_t server = NULL;
    http_server_config_t* config = make_server_config(5000, 5);

    err_t error = create_webserver(&server, config);
    printf("Ret=%d\n", error.error_nb);
    printf("Server=%p\n", server);

    error = start_webserver(server);

    if(error.error_nb != OK_ERROR) {
        printf("Errorcode=%d\nErrortext=%s\n", error.error_nb, error.error_msg);
        delete_webserver(server);
        printf("Free webserver\n");
        delete_server_config(config);
        printf("Free config\n");
    }

    while(1) {
        
    }
    return 0;
}