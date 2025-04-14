/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Versão modificada: utiliza média móvel de 50 posições e mostra
 * os valores de X, Y e a direção no display OLED, utilizando as
 * funções definidas em ssd1306_i2c.h.
 */

 #include <stdio.h>
 #include <string.h>
 #include "pico/stdlib.h"
 #include "hardware/adc.h"
 #include "inc/ssd1306.h"
 #include "inc/ssd1306_i2c.h"
 
 #define SDA_OLED 14
 #define SCL_OLED 15
 #define JOYSTICK_X 26
 #define JOYSTICK_Y 27
 #define BUFFER_SIZE 10
 
 int main(void) {
    stdio_init_all();

    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(SDA_OLED, GPIO_FUNC_I2C);
    gpio_set_function(SCL_OLED, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_OLED);
    gpio_pull_up(SCL_OLED);

    ssd1306_init();

    struct render_area frame_area = { 
        .start_column = 0,
        .end_column = ssd1306_width - 1,
        .start_page = 0,
        .end_page = ssd1306_n_pages - 1,
        .buffer_length = 0
    };

    calculate_render_area_buffer_length(&frame_area);

    uint8_t ssd[ssd1306_buffer_length];
    memset(ssd, 0, sizeof(ssd));

    adc_init();
    adc_gpio_init(JOYSTICK_X);
    adc_gpio_init(JOYSTICK_Y);

    uint16_t buffer_x[BUFFER_SIZE] = {0};
    uint16_t buffer_y[BUFFER_SIZE] = {0};
    uint32_t soma_x = 0;
    uint32_t soma_y = 0;
    uint indice = 0;
    uint amostras = 0;

    const uint adc_max = 4095;
    const uint centro = adc_max / 2;       
    const int margem = 300;

    while (1) {
        adc_select_input(0);
        uint16_t novo_x = adc_read();
        adc_select_input(1);
        uint16_t novo_y = adc_read();

        soma_x = soma_x - buffer_x[indice] + novo_x;
        soma_y = soma_y - buffer_y[indice] + novo_y;
        buffer_x[indice] = novo_x;
        buffer_y[indice] = novo_y;
        indice = (indice + 1) % BUFFER_SIZE;
        if (amostras < BUFFER_SIZE)
            amostras++;

        uint16_t media_x = soma_x / amostras;
        uint16_t media_y = soma_y / amostras;

        char direcao_horizontal[12] = "";
        char direcao_vertical[12] = "";
        if (media_x < centro - margem) {
            strcpy(direcao_horizontal, "B");
        } else if (media_x > centro + margem) {
            strcpy(direcao_horizontal, "C");
        }
        if (media_y < centro - margem) {
            strcpy(direcao_vertical, "E");
        } else if (media_y > centro + margem) {
            strcpy(direcao_vertical, "D");
        }

        char direcao[25] = "";
        if ((strlen(direcao_horizontal) == 0) && (strlen(direcao_vertical) == 0)) {
            strcpy(direcao, "X");
        } else if ((strlen(direcao_horizontal) > 0) && (strlen(direcao_vertical) > 0)) {
            sprintf(direcao, "%s - %s", direcao_vertical, direcao_horizontal);
        } else {
            sprintf(direcao, "%s - %s", direcao_vertical, direcao_horizontal);
        }

        char linha1[50];
        char linha2[50];
        sprintf(linha1, "X: %4d  Y: %4d", media_x, media_y);
        sprintf(linha2, "Dir: %s", direcao);

        memset(ssd, 0, sizeof(ssd));
        ssd1306_draw_string(ssd, 0, 0, linha1);
        ssd1306_draw_string(ssd, 0, 30, linha2);

        render_on_display(ssd, &frame_area);

        sleep_ms(10);
     }
     return 0;
 }
 