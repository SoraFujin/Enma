#include "../include/gpio.h"

void setup_gpio_B()
{
    DDRB &= ~(1 << DDB4); // Configure PB4 as input
    PORTB &= ~(1 << PB4); // Disable internal pull-up
}

void setup_gpio_A()
{
    PORTB |= (1 << PB5);  // Set output latch HIGH first
    DDRB |= (1 << DDB5);  // Configure PB5 as output
}

