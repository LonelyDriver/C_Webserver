#include <stdio.h>
#include <string.h>
#include "config_version.h"
#include "socketal.h"

int main(int argc, char** argv) {
    socket_t sock2;
    char buffer[0x0800] = {0x00};
    unsigned int rec = 0;

    printf("VERSION: %s\n", GetVersion());

    socket_t sock = Create_Socket(AF_INET, SOCK_STREAM, 0);
    printf("SOCKET: %d\n", sock);

    err_t ret = Bind(&sock, INADDR_ANY, 5000);
    if(ret.error_nb != 0) {
        printf("ERROR: %s\n", ret.error_msg);
        return 1;
    }
    ret = Listen(&sock);
    if(ret.error_nb != 0) {
        printf("ERROR: %s\n", ret.error_msg);
        return 1;
    }

    while(1) {
        ret = Accept(&sock, &sock2);
        if(ret.error_nb != 0) {
            printf("ERROR: %s\n", ret.error_msg);
            return 1;       
        }
        while(1) {
            rec = Receive_Tcp(&sock2, buffer, 0x0800);
            if(rec == 0) {
                printf("Client shutting down connection!\n");
                break;
            }else if(rec == -1) {
                printf("Error :(\n");
                break;
            }

            printf("Received len: %d\n", rec);
            printf("Received: %s|\n", buffer);
            printf("Cmp: %d\n",strcmp(buffer, "quit"));
            if (strcmp(buffer, "quit") == 0) {
                printf("Cya\n");
                break;
            }
            ret = Send_Tcp(&sock2, buffer, rec);
            if(ret.error_nb != 0) {
                printf("ERROR: %s\n", ret.error_msg);
                return 1;       
            }
            memset(buffer, 0x00, 0x0800);
        }
        Close(&sock2);
    }

    return 0;
}