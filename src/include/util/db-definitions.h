#pragma once


#define DATA_PATH "./data"

// SHM Paths
#define HANDLER_LOCK_SHM "./data/handlerlock"
#define SHARED_BUFFER_SHM "./data/sharedbuffer"
#define PAGE_TABLE_SHM "./data/pagetable"


// TODO: possible insecure use other mode + differentiate between mmaps
#define SHM_OPEN_MODE 0666 

#define MAX_NUMBER_OF_PKS 1 // TODO: for now only one. But maybe allow more in the future

#define MAX_STRING_SIZE 1024

#define SLOT_SIZE 1024 * 8 // 8 KB

#define SHARED_BUFFER_SLOTS 16384 // 2^14
