#include "pico/stdlib.h"
#include "kybercore.h"

int main()
{
    stdio_init_all();

    if (!init_led())
    {
        return -1; // Initialization failed
    }

    while (true)
    {
        toggle_led();  // Toggle the LED state
        sleep_ms(250); // Wait for 250 milliseconds
    }
}