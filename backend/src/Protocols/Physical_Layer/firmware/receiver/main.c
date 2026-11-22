#include "../../include/utils.h"
#include "../../include/receiver.h"
#include "../../include/gpio.h"

int main(void)
{
    setup_gpio_B();
    UART_init();

    uint8_t receive_data = 0;
    uint8_t expected_data = 18;

    while (1)
    {
        receive_data = receive_frame();

        UART_print("Received: ");
        UART_print_number(receive_data);
        UART_newline();

        if (receive_data == expected_data)
        {
            UART_print("Result: MATCH");
        }
        else
        {
            UART_print("Result: MISMATCH");
        }

        UART_newline();
        UART_newline();
    }

    return 0;
}

