## Overview
This project demonstrates TCP/IP communication using the STM32F746G Discovery board with LwIP stack. The client connects to a specified TCP server and continuously sends counter values in the format "counter:1", "counter:2", etc.

## Software
STM32CubeMX - For project configuration
STM32CubeIDE - For development and debugging
Netcat - For TCP server

## Folder dir 
f746g_TCP_basic/
├── Core/                   # Main application code
├── Drivers/                # STM32 HAL and BSP drivers
├── LWIP/                   # LwIP TCP/IP stack
├── TCP_App/                # Custom TCP client implementation
│   ├── Inc/              
│   │   ├── app_ethernet.h  # Ethernet management header
│   │   ├── TCP_client.h    # TCP client interface
│   │   └── uart_debug.h    # Debug output utilities
│   └── Src/
│       ├── app_ethernet.c  # Ethernet link management
│       ├── TCP_client.c    # TCP client implementation
│       └── uart_debug.c    # UART debug functions
│
└── Middlewares/            # Third-party middleware
    └── Third_Party/
        └── LwIP/           # LwIP source files

## Sample Output

![alt text](<Ekran görüntüsü 2025-06-02 003830.png>)