#include <stdio.h>
#include "config_version.h"
#include "socketal.h"

int main(int argc, char** argv) {
    printf("Hello it works\n");
    printf("VERSION: %s\n", GetVersion());

    socket_t sock = Create_Socket(AF_INET, SOCK_STREAM, 0);
    printf("SOCKET: %d\n", sock);

    socket_err ret = Connect(&sock, "localhost", 5000);
    printf("Ret: %d, %s\n", ret.error_nb, ret.error_msg);
    ret = Send(&sock, "Hello from example\n", 19);
    printf("Ret: %d, %s\n", ret.error_nb, ret.error_msg);
    return 0;
}