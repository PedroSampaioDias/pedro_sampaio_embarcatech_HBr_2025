# 📘 Leitor de Joystick com Média Móvel e OLED

🎯 **Objetivo do projeto**  
Desenvolver um programa em C que leia os valores analógicos convertidos digitalmente de um joystick da BitDogLab e exiba, no display OLED, os valores suavizados (por meio de uma média móvel) dos eixos X e Y, além de indicar a direção do movimento com caracteres simplificados.

---

🧩 **Componentes usados**  
- **Raspberry Pi Pico** ou placa compatível com o SDK do Pico  
- **Joystick da BitDogLab**  
- **Display OLED SSD1306** (interface I2C)  
- Bibliotecas:  
  - Pico SDK (pico/stdlib e hardware/adc)  
  - Biblioteca para controle do display: `ssd1306.h` e `ssd1306_i2c.h`

---

⚡ **Pinagem dos dispositivos**  
- **Display OLED (I2C):**  
  - SDA: GPIO 14  
  - SCL: GPIO 15  
- **Joystick:**  
  - Canal X: GPIO 26 (entrada ADC – canal 0)  
  - Canal Y: GPIO 27 (entrada ADC – canal 1)

---

🧪 **Como compilar e executar**  
1. **Configuração do Ambiente:**  
   - Instale e configure o [Raspberry Pi Pico SDK](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf) em sua máquina.  
   - Certifique-se de que as bibliotecas para o display OLED (`ssd1306.h` e `ssd1306_i2c.h`) estejam disponíveis e configuradas no diretório `inc/`.
2. **Compilação:**  
   - Crie uma pasta de build e utilize CMake para gerar os arquivos necessários:
     ```bash
     mkdir build && cd build
     cmake ..
     make
     ```
3. **Upload:**  
   - Conecte sua placa Raspberry Pi Pico ao computador (em modo de armazenamento USB) e copie o arquivo .uf2 gerado para a placa.
4. **Execução:**  
   - Após o upload, o programa iniciará automaticamente, realizando a leitura do joystick, processando a média móvel e atualizando o display OLED com os valores e a direção.

---

🖼️ **Imagens e vídeos**  
- **Circuito Montado:**  
  (Insira aqui uma foto do circuito, por exemplo: `![Circuito Montado](link_para_imagem_do_circuito)`)
- **Vídeo de Demonstração:**  
  (Insira o link para um vídeo de demonstração, por exemplo: `[Vídeo no YouTube](link_para_video)`)

---

📈 **Resultados esperados ou observados**  
- **Display OLED:**  
  - Linha 1: Exibição dos valores de X e Y, por exemplo:  
    `X: 1023  Y: 2047`
  - Linha 2: Exibição da direção em formato compacto, utilizando as seguintes letras:
    - “B” para indicar movimento para a esquerda (quando a média do eixo X estiver abaixo do limite inferior)
    - “C” para indicar movimento para a direita (quando a média do eixo X estiver acima do limite superior)
    - “E” para indicar movimento para cima (quando a média do eixo Y estiver abaixo do limite inferior)
    - “D” para indicar movimento para baixo (quando a média do eixo Y estiver acima do limite superior)
    - “X” para indicar que não há movimento significativo (os valores estão dentro da margem)
- **Atualização:**  
  - O display atualiza as leituras do joystick aproximadamente a cada 10ms, proporcionando uma resposta rápida e a visualização da média móvel das leituras.

---

