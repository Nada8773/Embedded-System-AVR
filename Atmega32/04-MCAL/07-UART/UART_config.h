/****************************************************************
 * Author  : Nada Mohamed
 * Data    : 9 Mar2020
 * Version : v01
 *****************************************************************/
#ifndef UART_CONFIG_H
#define UART_GONFIG_H

/* Option  UART_PARITY_DISABLED
 *         UART_PARITY_EVEN
 *         UART_PARITY_ODD */
#define UART_u8_PARITY       UART_PARITY_DISABLED

/* Option  UART_BAUDRATE_4800
 *         UART_BAUDRATE_9600
 *         UART_BAUDRATE_115200 */
#define UART_u8_BAUDRATE     UART_BAUDRATE_9600

/* Option  UART_STOP_1_BIT
 *         UART_STOP_2_BIT
 */
#define UART_u8_STOP_BITS    UART_STOP_1_BIT

/* Option  UART_SYS_FREQ_8M
 *         UART_SYS_FREQ_12M
 *         UART_SYS_FREQ_16M
 */
#define UART_u8_SYS_FREQ     UART_SYS_FREQ_8M


#define UART_u32_TIME_OUT    40000U
#endif
