#ifndef UART_DEBUG_H
#define UART_DEBUG_H

#include <stdint.h>

/* Debug levels */
typedef enum {
    DEBUG_LEVEL_ERROR = 0,
    DEBUG_LEVEL_WARN,
    DEBUG_LEVEL_INFO,
    DEBUG_LEVEL_DEBUG
} debug_level_t;

/* Function prototypes */
void uart_debug_init(void);
void uart_debug_print(debug_level_t level, const char *format, ...);

/* Convenience macros */
#define DEBUG_ERROR(...)   uart_debug_print(DEBUG_LEVEL_ERROR, __VA_ARGS__)
#define DEBUG_WARN(...)    uart_debug_print(DEBUG_LEVEL_WARN, __VA_ARGS__)
#define DEBUG_INFO(...)    uart_debug_print(DEBUG_LEVEL_INFO, __VA_ARGS__)
#define DEBUG_DEBUG(...)   uart_debug_print(DEBUG_LEVEL_DEBUG, __VA_ARGS__)

/* Printf redirect */
int _write(int file, char *ptr, int len);

#endif /* UART_DEBUG_H */
