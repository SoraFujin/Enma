#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

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

// returns 1 when it is a rasing edge else if it is a falling edge returns 0
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

uint8_t receive_frame()
{
    DDRB &= ~(1 << DDB4);
    PORTB &= ~(1 << PB4);
    while(1)
    {
        if(detect_edge() == 0)
        {
            _delay_ms(5);
            if(!(PINB & (1 << PB4)))
            {
                _delay_ms(10);
                return receive_byte();
            }
        }
    }
}

void send()
{
    DDRB |= (1 << DDB5);
    uint8_t data = 7;
    uint16_t frame_data = frame(data);
    send_frame(frame_data);
}

void setup_gpio_A()
{
    PORTB |= (1 << PB5);  // Set output latch HIGH first
    DDRB |= (1 << DDB5);  // Configure PB5 as output
}

void setup_gpio_B()
{
    DDRB &= ~(1 << DDB4); // Configure PB4 as input
    PORTB &= ~(1 << PB4); // Disable internal pull-up
}

int main(void) 
{
    setup_gpio_A();
    uint8_t data = 7;
    send_frame(frame(data));
    return 0;
}
