#include "uart_debug.h"
#include "usart.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

/* Current debug level */
static debug_level_t current_debug_level = DEBUG_LEVEL_INFO;

/* Debug level strings */
static const char *level_strings[] = {
    "[ERROR]",
    "[WARN ]",
    "[INFO ]",
    "[DEBUG]"
};

/* Initialize UART debug */
void uart_debug_init(void){
    /* Print startup message */
    uart_debug_print(DEBUG_LEVEL_INFO, "\r\n");
    uart_debug_print(DEBUG_LEVEL_INFO, "=====================================\r\n");
    uart_debug_print(DEBUG_LEVEL_INFO, "STM32F746G TCP Client\r\n");
    uart_debug_print(DEBUG_LEVEL_INFO, "Build: %s %s\r\n", __DATE__, __TIME__);
    uart_debug_print(DEBUG_LEVEL_INFO, "=====================================\r\n");
}

/* Print debug message with level */
void uart_debug_print(debug_level_t level, const char *format, ...){
    if (level > current_debug_level) {
        return;
    }

    char buffer[256];
    va_list args;

    /* Add timestamp in milliseconds */
    uint32_t tick = HAL_GetTick();
    int len = snprintf(buffer, sizeof(buffer), "[%7lu.%03lu] %s ",
                       tick / 1000, tick % 1000, level_strings[level]);

    /* Add user message */
    va_start(args, format);
    vsnprintf(buffer + len, sizeof(buffer) - len, format, args);
    va_end(args);

    /* Send to UART */
    HAL_UART_Transmit(&huart1, (uint8_t*)buffer, strlen(buffer), 100);
}

/* Printf redirect to UART */
int _write(int file, char *ptr, int len){
    HAL_UART_Transmit(&huart1, (uint8_t*)ptr, len, 100);
    return len;
}

/* For GCC compiler */
int __io_putchar(int ch){
    HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, 100);
    return ch;
}
