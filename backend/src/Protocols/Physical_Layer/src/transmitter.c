#include "../include/transmitter.h"
#include "../include/gpio.h"

void send_frame(uint16_t byte)
{
    uint16_t current_bit = 0;

    // this sends the bits in LSB starting with the least bit
    for(uint8_t i = 0; i < 10; ++i)
    {
        current_bit = byte >> i & 0b00000001;

        if (current_bit == 1)
        {
            PORTB |= (1 << PB5);
            _delay_ms(10);
        }

        if (current_bit == 0)
        {
            PORTB &= ~(1 << PB5);
            _delay_ms(10);
        }
    }
}

// First it adds padding to be able to hold 10 bits the byte when it gets it is only 8 bits so it is saved into 16 bit placeholder
// it does the left shift by 1 bit to set the last digit to 0 
// this sets the Least bit to zero in order to signal a start when does it start reading 
// and sets the 9th bit to one to know when to stop reading
// (HEX) 0x200 = (BINARY) 0b0000001000000000;
uint16_t frame(uint8_t byte)
{
    uint16_t frame = ((uint16_t) byte << 1) | 0x200;
    return frame;
}

int main(void) 
{
    setup_gpio_A();
    uint8_t data = 18;
    send_frame(frame(data));
    return 0;
}
