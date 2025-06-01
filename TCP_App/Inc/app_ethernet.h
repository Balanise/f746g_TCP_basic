#ifndef APP_ETHERNET_H
#define APP_ETHERNET_H

#include <stdint.h>

/* Ethernet States */
typedef enum {
    ETH_LINK_DOWN = 0,
    ETH_LINK_UP
} eth_link_state_t;

/* Function Prototypes */
void app_ethernet_init(void);
void app_ethernet_process(void);
eth_link_state_t app_ethernet_get_link_state(void);

#endif /* APP_ETHERNET_H */
