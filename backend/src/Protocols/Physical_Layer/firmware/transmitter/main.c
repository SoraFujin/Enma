#include "../../include/transmitter.h"
#include "../../include/utils.h"
#include "../../include/gpio.h"

int main(void) 
{
    UART_init();
    UART_print("Start Sending");
    setup_gpio_A();
    uint8_t data = 255;
    while(1)
    {
        send_frame(frame(data));
        UART_print("Start Sending");
        UART_newline();
    }
    return 0;
}
