#include "../include/hal_led.h"

int main() {
    gpio_stdio_init();

    while (true) {
        hal_led_toggle();
        sleep_ms(500);
    }
}
