#include "tcp_client.h"

/* Private Function Prototypes */
static void tcp_client_error(void *arg, err_t err);
static err_t tcp_client_sent(void *arg, struct tcp_pcb *tpcb, u16_t len);
static err_t tcp_client_connected(void *arg, struct tcp_pcb *tpcb, err_t err);
static err_t tcp_client_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);

/* Private variables */
static struct tcp_pcb *client_pcb = NULL;
static tcp_client_state_t client_state = TCP_STATE_DISCONNECTED;
static ip_addr_t server_ip;
static uint32_t reconnect_timer = 0;

/* Circular buffer for received data */
static char rx_buffer[TCP_RX_BUFFER_SIZE];
static volatile uint16_t rx_len = 0;
static volatile uint8_t rx_data_ready = 0;

/* Initialize TCP client */
void tcp_client_init(void){
    /* Convert IP string to ip_addr_t */
    ip4addr_aton(TCP_SERVER_IP, &server_ip);
    client_state = TCP_STATE_DISCONNECTED;

    /* Clear receive buffer */
    memset(rx_buffer, 0, TCP_RX_BUFFER_SIZE);
    rx_len = 0;
    rx_data_ready = 0;
}

/* Connect to TCP server */
void tcp_client_connect(void){
    err_t err;

    if (client_state != TCP_STATE_DISCONNECTED) {
        return;
    }

    /* Create new TCP PCB */
    client_pcb = tcp_new();
    if (client_pcb == NULL) {
        DEBUG_INFO("Error: Failed to create PCB\r\n");
        client_state = TCP_STATE_ERROR;
        return;
    }

    /* Set callbacks */
    tcp_arg(client_pcb, NULL);
    tcp_recv(client_pcb, tcp_client_recv);
    tcp_err(client_pcb, tcp_client_error);
    tcp_sent(client_pcb, tcp_client_sent);

    /* Connect to server */
    client_state = TCP_STATE_CONNECTING;
    err = tcp_connect(client_pcb, &server_ip, TCP_SERVER_PORT, tcp_client_connected);

    if (err != ERR_OK) {
        DEBUG_INFO("Error: Connection failed (%d)\r\n", err);
        tcp_close(client_pcb);
        client_pcb = NULL;
        client_state = TCP_STATE_ERROR;
    } else {
        DEBUG_INFO("Connecting to server...\r\n");
    }
}

/* Disconnect from server */
void tcp_client_disconnect(void){
    if (client_pcb != NULL) {
        tcp_close(client_pcb);
        client_pcb = NULL;
    }
    client_state = TCP_STATE_DISCONNECTED;
    DEBUG_INFO("Disconnected\r\n");
}

/* Send data to server */
void tcp_client_send(const char *data, uint16_t len){
    err_t err;

    if (client_state != TCP_STATE_CONNECTED || client_pcb == NULL) {
        DEBUG_INFO("Error: Not connected\r\n");
        return;
    }

    /* Write data */
    err = tcp_write(client_pcb, data, len, TCP_WRITE_FLAG_COPY);
    if (err == ERR_OK) {
        /* Flush the data */
        err = tcp_output(client_pcb);
        if (err != ERR_OK) {
            DEBUG_INFO("Error: tcp_output failed (%d)\r\n", err);
        }
    } else {
        DEBUG_INFO("Error: tcp_write failed (%d)\r\n", err);
    }
}

/* Process TCP client (call from main loop) */
void tcp_client_process(void){
    /* Auto-reconnect logic */
    if (client_state == TCP_STATE_ERROR || client_state == TCP_STATE_DISCONNECTED) {
        if (HAL_GetTick() - reconnect_timer > 3000) {  /* 3 second delay */
            reconnect_timer = HAL_GetTick();
            tcp_client_connect();
        }
    }
}

/* Get current connection state */
tcp_client_state_t tcp_client_get_state(void){
    return client_state;
}

/* Read string from receive buffer */
int tcp_client_read_string(char *buffer, uint16_t max_len){
    if (buffer == NULL || max_len == 0 || !rx_data_ready) {
        return 0;
    }

    /* Copy data */
    uint16_t copy_len = (rx_len < max_len - 1) ? rx_len : max_len - 1;
    memcpy(buffer, rx_buffer, copy_len);
    buffer[copy_len] = '\0';

    /* Clear the flag and buffer */
    rx_data_ready = 0;
    rx_len = 0;

    return copy_len;
}

/* Get number of bytes available in receive buffer */
uint16_t tcp_client_data_available(void){
    return rx_data_ready ? rx_len : 0;
}

/* Callback: Error occurred */
static void tcp_client_error(void *arg, err_t err){
    DEBUG_INFO("TCP Error: %d\r\n", err);
    client_pcb = NULL;  /* PCB is already freed by LwIP */
    client_state = TCP_STATE_ERROR;
}

/* Callback: Data sent successfully */
static err_t tcp_client_sent(void *arg, struct tcp_pcb *tpcb, u16_t len){
    /* Data sent successfully */
    return ERR_OK;
}

/* Callback: Data received from server */
static err_t tcp_client_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err){
    if (p != NULL) {
        /* Copy data to buffer if there's room */
        struct pbuf *q;
        uint16_t pos = 0;

        for (q = p; q != NULL && pos < TCP_RX_BUFFER_SIZE - 1; q = q->next) {
            uint16_t copy_len = q->len;
            if (pos + copy_len > TCP_RX_BUFFER_SIZE - 1) {
                copy_len = TCP_RX_BUFFER_SIZE - 1 - pos;
            }

            memcpy(rx_buffer + pos, q->payload, copy_len);
            pos += copy_len;
        }

        rx_buffer[pos] = '\0';
        rx_len = pos;
        rx_data_ready = 1;

        /* Free the buffer */
        tcp_recved(tpcb, p->tot_len);
        pbuf_free(p);
    } else {
        /* Connection closed by server */
        tcp_client_disconnect();
    }

    return ERR_OK;
}
/* Callback: Connected */
static err_t tcp_client_connected(void *arg, struct tcp_pcb *tpcb, err_t err){
    if (err == ERR_OK) {
        client_state = TCP_STATE_CONNECTED;
    } else {
        client_state = TCP_STATE_ERROR;
    }

    return ERR_OK;
}
