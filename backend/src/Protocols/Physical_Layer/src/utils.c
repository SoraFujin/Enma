#include "../include/utils.h"

void UART_init(void)
{
    // Set baud rate
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
    UBRR0L = (uint8_t)UBRR_VALUE;

    // Enable USART transmitter
    UCSR0B |= (1 << TXEN0);

    // 8 data bits, 1 stop bit, no parity
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void UART_transmit_char(char data)
{
    // Wait until transmit buffer is empty
    while (!(UCSR0A & (1 << UDRE0)));

    UDR0 = data;
}

void UART_print(const char *str)
{
    while (*str)
    {
        UART_transmit_char(*str++);
    }
}

void UART_print_number(uint8_t number)
{
    if (number >= 100)
        UART_transmit_char('0' + number / 100);

    if (number >= 10)
        UART_transmit_char('0' + (number / 10) % 10);

    UART_transmit_char('0' + number % 10);
}

void UART_newline(void)
{
    UART_transmit_char('\r');
    UART_transmit_char('\n');
}

