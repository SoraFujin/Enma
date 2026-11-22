#ifndef UTILS_H
#define UTILS_H

#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1)

#include <avr/io.h>


void UART_init(void);

void UART_transmit_char(char data);

void UART_print(const char *str);

void UART_print_number(uint8_t number);

void UART_newline(void);

void UART_print_big_number(uint16_t number);

#endif
