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

void UART_print_big_number(uint16_t number)
{
    char buffer[6];
    uint8_t i = 0;

    if (number == 0)
    {
        UART_transmit_char('0');
        return;
    }

    while (number > 0)
    {
        buffer[i++] = '0' + (number % 10);
        number /= 10;
    }

    while (i > 0)
    {
        UART_transmit_char(buffer[--i]);
    }
}

void UART_print_number(uint32_t number, uint8_t base)
{
    if (base < 2 || base > 16)
        return;

    char buffer[32];
    uint8_t i = 0;

    const char digits[] = "0123456789ABCDEF";

    if (number == 0)
    {
        UART_transmit_char('0');
        return;
    }

    while (number > 0)
    {
        buffer[i++] = digits[number % base];
        number /= base;
    }

    while (i > 0)
    {
        UART_transmit_char(buffer[--i]);
    }
}

void UART_newline(void)
{
    UART_transmit_char('\r');
    UART_transmit_char('\n');
}

