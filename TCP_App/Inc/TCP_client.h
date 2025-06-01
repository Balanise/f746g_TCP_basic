#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

/* Peripheral includes */
#include "lwip/tcp.h"
#include "lwip/inet.h"

/* Local includes */
#include "uart_debug.h"
#include "main.h"

/* C library includes */
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* TCP Connection States */
typedef enum {
    TCP_STATE_DISCONNECTED = 0,
    TCP_STATE_CONNECTING,
    TCP_STATE_CONNECTED,
    TCP_STATE_ERROR
} tcp_client_state_t;

/* Server Configuration */
#define TCP_SERVER_IP     "192.168.1.35"
#define TCP_SERVER_PORT   5005
#define TCP_CLIENT_PORT   5006

/* Receive Buffer Configuration */
#define TCP_RX_BUFFER_SIZE  1024

/* Function Prototypes */
void tcp_client_init(void);
void tcp_client_connect(void);
void tcp_client_disconnect(void);
void tcp_client_send(const char *data, uint16_t len);
void tcp_client_process(void);
tcp_client_state_t tcp_client_get_state(void);
int tcp_client_read_string(char *buffer, uint16_t max_len); // Unused for this project
uint16_t tcp_client_data_available(void); // Unused for this project

#endif /* TCP_CLIENT_H */
