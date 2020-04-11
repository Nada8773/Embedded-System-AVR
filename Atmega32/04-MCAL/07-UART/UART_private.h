/****************************************************************
 * Author  : Nada Mohamed
 * Data    : 9 Mar2020
 * Version : v01
 *****************************************************************/

#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H

/* UCSRA BITS */
#define UCSRA_RXC                                     7
#define UCSRA_TXC                                     6
#define UCSRA_UDRE                                    5
#define UCSRA_FE                                      4
#define UCSRA_DOR                                     3
#define UCSRA_PE                                      2
#define UCSRA_U2X                                     1
#define UCSRA_MPCM                                    0

/* UCSRB BITS */
#define UCSRB_RXCIE                                   7
#define UCSRB_TXCIE                                   6
#define UCSRB_UDRIE                                   5
#define UCSRB_RXEN                                    4
#define UCSRB_TXEN                                    3
#define UCSRB_UCSZ2                                   2
#define UCSRB_RXB9                                    1
#define UCSRB_TXb9                                    0


/* UCSRC BITS */
#define UCSRC_URSEL                                   7
#define UCSRC_UMSEL                                   6
#define UCSRC_UPM1                                    5
#define UCSRC_UPM0                                    4
#define UCSRC_USBS                                    3
#define UCSRC_UCSZ1                                   2
#define UCSRC_UCSZ0                                   1
#define UCSRC_UCPOL                                   0


#define  UART_PARITY_DISABLED   0U
#define  UART_PARITY_EVEN       2U
#define  UART_PARITY_ODD        3U


#define  UART_BAUDRATE_4800     0U
#define  UART_BAUDRATE_9600     1U
#define  UART_BAUDRATE_115200   2U


#define  UART_SYS_FREQ_8M       0U
#define  UART_SYS_FREQ_12M      1U
#define  UART_SYS_FREQ_16M      2U

#define UART_STOP_1_BIT         0U
#define UART_STOP_2_BIT         1U


#endif
