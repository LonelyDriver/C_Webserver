#include "error_handling.h"

static const char* socket_errors[] = {
    {"OK"},
    {"Could not create socket"},
    {"Invalid ip address or port"},
    {"Trying to connect to invalid server"},
    {"Could not connect to server"},
    {"Buffer invalid size or type"},
    {"Could not sent data"},
    {"Could not sent all data"},
    {"Invalid socket"},
    {"Receiving data failed"},
    {"Could not close socket"},
    {"Could not bind socket"},
    {"Could not listen socket"},
    {"Accept socket failed"}
};

const char* GetErrorMessage(ERRR error){
    return socket_errors[error];
}