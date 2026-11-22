#ifndef RECEIVER_H
#define RECEIVER_H

#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1)

#include <avr/io.h>
#include <util/delay.h>

uint8_t receive_byte();
uint8_t receive_frame();
uint8_t detect_edge();

#endif
