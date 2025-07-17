#pragma once


#define DATA_PATH "./data"

#define HANDLER_LOCK_SHM "/handlerlock"

// TODO: possible insecure use other mode + differentiate between mmaps
#define SHM_OPEN_MODE 0666 

#define MAX_NUMBER_OF_PKS 1 // TODO: for now only one. But maybe allow more in the future

#define MAX_STRING_SIZE 1024