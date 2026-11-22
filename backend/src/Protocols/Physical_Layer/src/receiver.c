#include "../include/receiver.h"

uint8_t receive_byte()
{
    uint8_t byte = 0;
    for (uint8_t i = 0; i < 8; ++i) 
    {
        if(PINB & (1 << PB4)) 
        {
            byte |= (1 << i); 
            _delay_ms(10);
        } else {
            byte &= ~(1 << i);
            _delay_ms(10);
        }
    }
    return byte;
}

// returns 1 when it is a raising edge else if it is a falling edge returns 0
uint8_t detect_edge() 
{
    uint8_t prev_bit = 1;
    uint8_t current_bit = 0;
    while(1) 
    {
        prev_bit = (PINB & (1 << PB4)) ? 1 : 0;
        _delay_ms(0.1);
        current_bit = (PINB & (1 << PB4)) ? 1 : 0;
        if (prev_bit != current_bit)
        {
            return current_bit == 1 ? 1 : 0;
        }
    }
}

uint8_t receive_frame()
{
    uint8_t data = 0;
    while(1)
    {
        if(detect_edge() == 0)
        {
            _delay_ms(5);
            if(!(PINB & (1 << PB4)))
            {
                _delay_ms(10);
                data = receive_byte();
                _delay_ms(10);
                if(PINB & (1 << PB4)) 
                    return data;
            }
        }
    }
}
