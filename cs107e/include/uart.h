#ifndef UART_H
#define UART_H

#include <stdbool.h>

/*
 * Hardware abstractions for a serial port (UART).
 *
 * Author: Pat Hanrahan <hanrahan@cs.stanford.edu>
 * Date: Jan 24, 2016
 */

enum {
    EOT = 4,  // Output end of transmission to indicate uart communication complete
    EOF = -1  // Receive end of file when no more data to read

};

/*
 * Initialize the UART code module. The init function should be called
 * once before any calls to other functions in the uart module. The
 * UART requires exclusive use of GPIO pins 14 (transmit) and 15 (receive).
 * Once the uart is initialized and in use, your code should not
 * muck with these two pins.
 * It is possible, although rare, to call uart_init() again to
 * reset the UART state. A re-initialization will discard any
 * pending data in the send/receive buffer.
 */
void uart_init(void);

/*
 * Obtains the next input character from the serial port and returns it.
 * If receive buffer is empty, will block until next character is received.
 *
 * @return    the character read or EOF if error or at end of input
 */
int uart_getchar(void);

/*
 * Outputs a character to the serial port.
 * If send buffer is full, will block until space available.
 *
 * @param ch   the character to write to the serial port
 * @return     the character written
 */
int uart_putchar(int ch);

/*
 * Flushes any output characters pending in the send buffer.
 */
void uart_flush(void);

/*
 * Returns true if there is a character ready to be read, false otherwise.
 */
bool uart_haschar(void);

/*
 * Outputs a string to the serial port by calling uart_putchar()
 * on each character.
 *
 * @param str  the string to output
 * @return     the count of characters written or EOF if error
 */
int uart_putstring(const char *str);

/*
 * Outputs raw byte to the serial port. uart_send outputs the raw byte
 * with no translation (unlike uart_putchar which adds processing for
 * converting end-of-line markers). To send text character, use
 * uart_putchar; if raw binary data, use uart_send.
 *
 * @param byte   the byte to write to the serial port
 */
void uart_send(unsigned char byte);

/*
 * Obtain raw byte from the serial port. uart_recv returns the raw
 * byte with no translation (unlike uart_getchar which adds processing
 * for converting end-of-line and end-of-file markers). To read text
 * character, use uart_getchar; if raw binary data, use uart_recv.
 *
 * @return   the byte read from the serial port
 */
unsigned char uart_recv(void);


#endif
