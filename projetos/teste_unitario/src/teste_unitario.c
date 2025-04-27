#include "unity.h"
#include <stdint.h>
#include <stdio.h>

void setUp(void)    {}
void tearDown(void) {}

float converte_adc_para_celsius(uint16_t valor_adc) {
    const float vref    = 3.3f;
    const float vmax    = 4095.0f;
    const float v25     = 0.706f;
    const float declive = 0.001721f;
    float tensao = (valor_adc * vref) / vmax;
    return 27.0f - ((tensao - v25) / declive);
}

typedef struct {
    uint16_t valor_adc;
    float    esperado;
} CasoTeste;

static const CasoTeste casosTeste[] = {
    { 934,  0.0f  },
    { 923,  5.0f  },
    { 912, 10.0f  },
    { 902, 15.0f  },
    { 891, 20.0f  },
    { 880, 25.0f  },
    { 870, 30.0f  },
    { 859, 35.0f  },
    { 848, 40.0f  },
    { 838, 45.0f  },
    { 827, 50.0f  }
};

#define NUM_CASOS  (sizeof(casosTeste) / sizeof(casosTeste[0]))
#define TOLERANCIA 0.2f

void teste_parametrizado_adc_para_celsius(void) {
    for (size_t i = 0; i < NUM_CASOS; ++i) {
        float resultado = converte_adc_para_celsius(casosTeste[i].valor_adc);
        char mensagem[64];
        snprintf(mensagem, sizeof(mensagem),
                 "Falha (adc=%u): esperado %.2f, obteve %.2f",
                 casosTeste[i].valor_adc,
                 casosTeste[i].esperado,
                 resultado);
        TEST_ASSERT_FLOAT_WITHIN_MESSAGE(
            TOLERANCIA,
            casosTeste[i].esperado,
            resultado,
            mensagem
        );
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(teste_parametrizado_adc_para_celsius);
    return UNITY_END();
}
