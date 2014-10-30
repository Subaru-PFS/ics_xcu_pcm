#ifndef __TCPIPCONFIG_H
#define __TCPIPCONFIG_H

#include "GenericTypeDefs.h"
#include "Compiler.h"

#define STACK_USE_DHCP_CLIENT    
#define STACK_USE_ICMP_SERVER    
#define STACK_USE_TCP            
#define STACK_USE_ARP
#define STACK_USE_UDP            

#define STACK_CCS_SMTP_TX_SIZE    0
#define STACK_CCS_SMTP_RX_SIZE    0

#define STACK_CCS_HTTP2_SERVER_TX_SIZE    0
#define STACK_CCS_HTTP2_SERVER_RX_SIZE    0

#define STACK_MY_TELNET_SERVER_TX_SIZE    0
#define STACK_MY_TELNET_SERVER_RX_SIZE    0

#define MY_DEFAULT_HOST_NAME      "PCM_CONTROLLER"
#define MY_UNIT_HOSTNAME "PCM_CONTROLLER"

#define MY_DEFAULT_IP_ADDR_BYTE1   192ul
#define MY_DEFAULT_IP_ADDR_BYTE2   168ul
#define MY_DEFAULT_IP_ADDR_BYTE3   2ul
#define MY_DEFAULT_IP_ADDR_BYTE4   200ul

#define MY_DEFAULT_MASK_BYTE1      255ul
#define MY_DEFAULT_MASK_BYTE2      255ul
#define MY_DEFAULT_MASK_BYTE3      255ul
#define MY_DEFAULT_MASK_BYTE4      0ul

#define MY_DEFAULT_GATE_BYTE1      192ul
#define MY_DEFAULT_GATE_BYTE2      168ul
#define MY_DEFAULT_GATE_BYTE3      2ul
#define MY_DEFAULT_GATE_BYTE4      1ul

#define MY_DEFAULT_MAC_BYTE1      (0x0)
#define MY_DEFAULT_MAC_BYTE2      (0x20)
#define MY_DEFAULT_MAC_BYTE3      (0x30)
#define MY_DEFAULT_MAC_BYTE4      (0x40)
#define MY_DEFAULT_MAC_BYTE5      (0x50)
#define MY_DEFAULT_MAC_BYTE6      (0x60)

#define UDP_DEST_PORT 1025
#define UDP_SOURCE_PORT 1024
#define TCP_LISTEN_PORT 1000
#define NUM_LISTEN_SOCKETS 2

#define TCP_CONFIGURATION NUM_LISTEN_SOCKETS
#define TCP_ETH_RAM_SIZE 1000
#define TCP_PIC_RAM_SIZE 0
#define TCP_SPI_RAM_SIZE 0
#define TCP_SPI_RAM_BASE_ADDRESS 0

//!#define TCP_ETH_RAM_SIZE (STACK_CCS_SMTP_TX_SIZE + \
//!                          STACK_CCS_SMTP_RX_SIZE + \
//!                          STACK_CCS_HTTP2_SERVER_TX_SIZE + \
//!                          STACK_CCS_HTTP2_SERVER_RX_SIZE + \
//!                          STACK_MY_TELNET_SERVER_TX_SIZE + \
//!                          STACK_MY_TELNET_SERVER_RX_SIZE + \
//!                          100*TCP_CONFIGURATION)                       

// Define names of socket types
#define TCP_PURPOSE_GENERIC_TCP_CLIENT 0
#define TCP_PURPOSE_GENERIC_TCP_SERVER 1
#define TCP_PURPOSE_TELNET             2
#define TCP_PURPOSE_FTP_COMMAND        3
#define TCP_PURPOSE_FTP_DATA           4
#define TCP_PURPOSE_TCP_PERFORMANCE_TX 5
#define TCP_PURPOSE_TCP_PERFORMANCE_RX 6
#define TCP_PURPOSE_UART_2_TCP_BRIDGE  7
#define TCP_PURPOSE_HTTP_SERVER        8
#define TCP_PURPOSE_DEFAULT            9
#define TCP_PURPOSE_BERKELEY_SERVER    10
#define TCP_PURPOSE_BERKELEY_CLIENT    11
#define TCP_PURPOSE_CCS_SMTP           0x40

typedef struct
{
   BYTE vSocketPurpose;
   BYTE vMemoryMedium;
   WORD wTXBufferSize;
   WORD wRXBufferSize;
} TCPSocketInitializer_t;

TCPSocketInitializer_t TCPSocketInitializer[TCP_CONFIGURATION] =
{
   //{TCP_PURPOSE_GENERIC_TCP_SERVER, TCP_ETH_RAM, 200, 300},
   //{TCP_PURPOSE_GENERIC_TCP_SERVER, TCP_ETH_RAM, 200, 300}
   {TCP_PURPOSE_DEFAULT, TCP_ETH_RAM, 200, 200},
   {TCP_PURPOSE_DEFAULT, TCP_ETH_RAM, 200, 200}
};

#ifndef MAX_HTTP_CONNECTIONS
   #define  MAX_HTTP_CONNECTIONS 1
#endif
#ifndef MAX_UDP_SOCKETS
   #define MAX_UDP_SOCKETS 10
#endif

#endif
