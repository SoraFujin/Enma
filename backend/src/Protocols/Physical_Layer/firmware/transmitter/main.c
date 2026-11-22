#include "../../include/transmitter.h"
#include "../../include/gpio.h"

int main(void) 
{
    setup_gpio_A();
    uint8_t data = 7;
    send_frame(frame(data));
    return 0;
}
