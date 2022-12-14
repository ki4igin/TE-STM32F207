#ifndef __UDP_C_H
#define __UDP_C_H

#include "stdint.h"

void udp_client_connect(void);
void udp_client_send(void *data, uint32_t size);

#endif
