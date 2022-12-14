#include "udp_c.h"
#include "lwip/udp.h"
#include "leds.h"

struct udp_pcb *udp_c;

void udp_recv_callback(
    void *arg,
    struct udp_pcb *upcb,
    struct pbuf *p,
    const ip_addr_t *addr,
    uint16_t port)
{
    pbuf_free(p);
}

void udp_client_connect(void)
{
    err_t err;

    udp_c = udp_new();

    ip_addr_t my_ipaddr;
    IP_ADDR4(&my_ipaddr, 192, 168, 0, 10);
    udp_bind(udp_c, &my_ipaddr, 8);

    ip_addr_t dest_ipaddr;
    IP_ADDR4(&dest_ipaddr, 192, 168, 0, 5);
    err = udp_connect(udp_c, &dest_ipaddr, 7);

    if (err == ERR_OK) {
        /* 2. Send message to server */
        /* 3. Set a receive callback for the upcb */
        udp_recv(udp_c, udp_recv_callback, NULL);
    }
}

uint32_t temp;
struct pbuf *pbuf;

void udp_client_send(void *data, uint32_t size)
{
    err_t err;
    static uint32_t cnt = 0;
    /* allocate pbuf from pool*/
    pbuf = pbuf_alloc(PBUF_TRANSPORT, size, PBUF_RAM);

    if (pbuf != NULL) {
        /* copy data to pbuf */
        err = pbuf_take(pbuf, data, size);
        if (err != ERR_OK) {
            temp = err;
            led_on();
        }

        /* send udp data */
        err = udp_send(udp_c, pbuf);
        if (err != ERR_OK) {
            cnt++;
            temp = err;
            led_toggle();
        }

        /* free pbuf */
        pbuf_free(pbuf);
    }
}
