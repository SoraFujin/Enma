#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void send_frame(uint16_t byte);
uint16_t frame(uint8_t byte);

#endif // !TRANSMITTER_H
