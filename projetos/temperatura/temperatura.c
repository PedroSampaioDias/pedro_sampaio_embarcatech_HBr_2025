#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "inc/ssd1306_i2c.h"

#define SDA_OLED 14
#define SCL_OLED 15
#define MA_WINDOW 1000

static struct render_area frame_area;
static uint8_t ssd[ssd1306_buffer_length];

void update_display(int temperature) {
    memset(ssd, 0, sizeof(ssd));
    char linha1[16];
    sprintf(linha1, "Temp: %d C", temperature);
    ssd1306_draw_string(ssd, 0, 0, linha1);
    render_on_display(ssd, &frame_area);
}

int main(void) {
    stdio_init_all();
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
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);
    const float conversion_factor = 3.3f / (1 << 12);
    float temp_buffer[MA_WINDOW] = {0};
    int ma_index = 0;
    int count = 0;
    float sum = 0.0f;
    while (true) {
        uint16_t raw = adc_read();
        float voltage = raw * conversion_factor;
        float temperature = 27.0f - (voltage - 0.706f) / 0.001721f;
        if (count < MA_WINDOW) {
            sum += temperature;
            temp_buffer[ma_index] = temperature;
            count++;
        } else {
            sum = sum - temp_buffer[ma_index] + temperature;
            temp_buffer[ma_index] = temperature;
        }
        int avg_temperature = (int)((sum / count) * 0.702702703);
        ma_index = (ma_index + 1) % MA_WINDOW;
        update_display(avg_temperature);
        sleep_ms(500);
    }
    return 0;
}
