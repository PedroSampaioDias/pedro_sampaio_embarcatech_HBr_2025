# 📘 Conversão ADC → °C (Testes Unitários)

🎯 **Objetivo do projeto**  
Demonstrar a escrita e execução de testes unitários parametrizados em C usando o framework [Unity](https://github.com/ThrowTheSwitch/Unity) para validar a função que converte um valor de ADC (12 bits) em graus Celsius.

---

🧩 **Componentes usados**  
- Biblioteca de testes **Unity** (ThrowTheSwitch)  
- **GCC** (ou outro compilador C compatível)  
- Sistema operacional Ubuntu (qualquer distro Linux com `bash`)

---

⚡ **Pinagem dos dispositivos**  
> **Não aplicável**  
> Este repositório contém apenas código de teste em **host** (PC), sem interação direta com hardware ou Raspberry Pi Pico W.

---

🧪 **Como compilar e executar**  

1. **Instalar dependências**  
   ```bash
   sudo apt update
   sudo apt install build-essential git

   # Obter o Unity
    git clone https://github.com/ThrowTheSwitch/Unity.git

    # Compilar os testes
    gcc -o teste_unitario \
        src/teste_unitario.c \
        Unity/src/unity.c \
        -I Unity/src

    # Executar
    ./teste_unitario
   ```

    Você deverá ver algo como:

    ```bash
    src/teste_unitario.c:59:teste_parametrizado_adc_para_celsius:PASS

    -----------------------
    1 Tests 0 Failures 0 Ignored 
    OK

    ```