#ifndef __HTTP_IO_H__
#define __HTTP_IO_H__

#include "c_types.h"

typedef void (* soc_recv_callback)(char *data, unsigned short len);

void ICACHE_FLASH_ATTR e_soc_creat(char *host, 
    int port, 
    char *send_data, 
    soc_recv_callback recv_handler);

void ICACHE_FLASH_ATTR e_soc_send(const char *data, int len);

void ICACHE_FLASH_ATTR e_soc_close();
#endif