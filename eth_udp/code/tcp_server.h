#ifndef __TCP_SERVER_H
#define __TCP_SERVER_H

#include "stdint.h"

void echo_init(void);
void tcp_server_send(void *data, uint32_t size);

#endif
