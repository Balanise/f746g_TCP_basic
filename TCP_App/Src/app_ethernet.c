#include "app_ethernet.h"
#include "lwip/netif.h"
#include "lwip/tcpip.h"
#include "ethernetif.h"
#include "uart_debug.h"
#include "main.h"
#include <stdio.h>

/* External variables from LwIP */
extern struct netif gnetif;
extern ETH_HandleTypeDef heth;

/* Private variables */
static eth_link_state_t eth_link_state = ETH_LINK_DOWN;
static uint32_t link_timer = 0;

/* PHY Address - LAN8742A on Discovery board */
#define PHY_ADDRESS     0x00

/* Initialize Ethernet application */
void app_ethernet_init(void){
    /* Nothing extra needed - LwIP init is done in main.c */
    DEBUG_INFO("Ethernet initialized\r\n");
    DEBUG_INFO("IP: %s\r\n", ip4addr_ntoa(&gnetif.ip_addr));
}

/* Process Ethernet link status */
void app_ethernet_process(void){
    uint32_t phyreg = 0;

    /* Check link status every 1 second */
    if (HAL_GetTick() - link_timer < 1000) {
        return;
    }
    link_timer = HAL_GetTick();

    /* Read PHY status register */
    HAL_ETH_ReadPHYRegister(&heth, PHY_ADDRESS, PHY_BSR, &phyreg);

    /* Check link status */
    if ((phyreg & PHY_LINKED_STATUS) && (eth_link_state == ETH_LINK_DOWN)) {
        /* Link is up */
        eth_link_state = ETH_LINK_UP;
        netif_set_link_up(&gnetif);
        DEBUG_INFO("Ethernet Link: UP\r\n");

    } else if (!(phyreg & PHY_LINKED_STATUS) && (eth_link_state == ETH_LINK_UP)) {
        /* Link is down */
        eth_link_state = ETH_LINK_DOWN;
        netif_set_link_down(&gnetif);
        DEBUG_INFO("Ethernet Link: DOWN\r\n");
    }
}

/* Get current link state */
eth_link_state_t app_ethernet_get_link_state(void){
    return eth_link_state;
}
