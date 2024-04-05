#include <stdio.h>
#include <string>
//#include <stdlib.h>
#include "pico/stdlib.h"


int main() {
    stdio_init_all();
   // while (!stdio_usb_connected())
    //    sleep_ms(100);

    // loop
    while(true){
        int pin = 2, outVal = 0;
            printf("IN [Pin %2d]: %d\n", pin, gpio_get(pin));
            gpio_put(pin, outVal);
            gpio_init(pin);
            gpio_set_dir(pin, GPIO_IN);
            gpio_pull_up(pin);
            sleep_ms(100);
    }

    return 0;
}