#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/irq.h"
#include "pico/time.h"

#include "inc/ssd1306.h"
#include "inc/ssd1306_i2c.h"

#define SDA_OLED 14
#define SCL_OLED 15

#define BUTTON_A_PIN 5
#define BUTTON_B_PIN 6

#define DEBOUNCE_DELAY_US 50000

volatile bool em_contagem = false;
volatile int contador = 0;
volatile int clicks_b = 0;
volatile uint64_t last_press_a = 0;
volatile uint64_t last_press_b = 0;

static struct render_area frame_area;
static uint8_t ssd[ssd1306_buffer_length];

void update_display(int cont, int clicks) {
    memset(ssd, 0, sizeof(ssd));
    char linha1[16];
    char linha2[16];
    sprintf(linha1, "Timer %d", cont);
    sprintf(linha2, "Cliques %d", clicks);
    ssd1306_draw_string(ssd, 0, 0, linha1);
    ssd1306_draw_string(ssd, 0, 30, linha2);
    render_on_display(ssd, &frame_area);
}

bool countdown_timer_callback(repeating_timer_t *rt) {
    if (!em_contagem) return true;

    if (contador > 0) {
        update_display(contador, clicks_b);
        contador--;
    } 
    else if (contador == 0) {
        update_display(0, clicks_b);
        em_contagem = false;
    }
    return true;
}

void gpio_callback(uint gpio, uint32_t events) {
    uint64_t now = time_us_64();

    if (gpio == BUTTON_A_PIN && (events & GPIO_IRQ_EDGE_FALL)) {
        if ((now - last_press_a) < DEBOUNCE_DELAY_US) return;
        last_press_a = now;

        contador = 9;
        clicks_b = 0;
        em_contagem = true;
        update_display(contador, clicks_b);
    }

    if (gpio == BUTTON_B_PIN && (events & GPIO_IRQ_EDGE_FALL)) {
        if ((now - last_press_b) < DEBOUNCE_DELAY_US) return;
        last_press_b = now;

        if (em_contagem && contador > 0) {
            clicks_b++;
            update_display(contador, clicks_b);
        }
    }
}

int main(void) {
    stdio_init_all();

    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);

    gpio_init(BUTTON_B_PIN);
    gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_B_PIN);

    gpio_set_irq_enabled_with_callback(BUTTON_A_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    gpio_set_irq_enabled(BUTTON_B_PIN, GPIO_IRQ_EDGE_FALL, true);

    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(SDA_OLED, GPIO_FUNC_I2C);
    gpio_set_function(SCL_OLED, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_OLED);
    gpio_pull_up(SCL_OLED);

    ssd1306_init();

    frame_area.start_column = 0;
    frame_area.end_column   = ssd1306_width - 1;
    frame_area.start_page   = 0;
    frame_area.end_page     = ssd1306_n_pages - 1;
    frame_area.buffer_length = 0;
    calculate_render_area_buffer_length(&frame_area);

    memset(ssd, 0, sizeof(ssd));
    render_on_display(ssd, &frame_area);

    contador = 9;
    clicks_b = 0;
    em_contagem = true;
    update_display(contador, clicks_b);

    repeating_timer_t timer;
    add_repeating_timer_ms(1000, countdown_timer_callback, NULL, &timer);

    while (true) {
        tight_loop_contents();
    }
    return 0;
}
