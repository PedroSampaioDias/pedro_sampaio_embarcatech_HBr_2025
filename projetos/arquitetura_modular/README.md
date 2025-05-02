# 📘 Piscar LED Modular - Raspberry Pi Pico W

🎯 **Objetivo do projeto**  
Este projeto demonstra como estruturar de forma modular um código para piscar o LED embutido da Raspberry Pi Pico W, usando uma divisão clara entre driver de hardware, camada de abstração (HAL) e aplicação principal.

---

🧩 **Componentes usados**  
- Raspberry Pi Pico W  
- SDK do Raspberry Pi Pico (pico-sdk)  
- Biblioteca cyw43_arch (para controle do Wi-Fi e LED)

---

⚡ **Pinagem dos dispositivos**  
O LED utilizado é o LED embutido do módulo Wi-Fi (CYW43) da Raspberry Pi Pico W, controlado via `CYW43_WL_GPIO_LED_PIN`.

---

🧪 **Como compilar e executar**

1. **Pré-requisitos:**
   - Instale o [pico-sdk](https://github.com/raspberrypi/pico-sdk) e configure o ambiente CMake.
   - Certifique-se de ter o `cmake` e `make` instalados.

2. **Compilação:**
   ```bash
   mkdir build
   cd build
   cmake ..
   make
