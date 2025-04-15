# 📘 Média Móvel de Temperatura com Raspberry Pi Pico e Display OLED

🎯 **Objetivo do projeto**  
O projeto tem como objetivo demonstrar a aquisição de dados de temperatura utilizando o sensor interno do Raspberry Pi Pico, o processamento desses dados através de um filtro de média móvel com 50 amostras para suavização dos sinais, e a exibição do valor resultante (em graus Celsius, como número inteiro) em um display OLED via comunicação I2C.

---

🧩 **Componentes usados**  
- Raspberry Pi Pico  
- Display OLED com controlador SSD1306  
- Bibliotecas e SDKs:  
  - Pico SDK (incluindo pico/stdlib.h, hardware/adc.h e hardware/i2c.h)  
  - Biblioteca SSD1306 para gerenciamento do display (incorporada via inc/ssd1306.h e inc/ssd1306_i2c.h)

---

⚡ **Pinagem dos dispositivos**  
- Display OLED (I2C):  
  - SDA conectado ao pino 14 do Pico  
  - SCL conectado ao pino 15 do Pico  
- Sensor de Temperatura:  
  - Utiliza o sensor interno do Raspberry Pi Pico (acessado via ADC na entrada 4)

---

🧪 **Como compilar e executar**  
1. Pré-requisitos:  
   - Instale o Raspberry Pi Pico SDK e configure seu ambiente de desenvolvimento conforme a documentação oficial.  
   - Certifique-se de ter o CMake e as ferramentas de compilação instaladas.

2. Clonando o Repositório:  
   - Execute: git clone https://seu-repositorio-url.git  
   - Em seguida: cd nome-do-projeto

3. Compilação:  
   - Crie uma pasta de build e acesse-a: mkdir build && cd build  
   - Configure o projeto com CMake: cmake ..  
   - Compile o projeto: make

4. Upload para o Raspberry Pi Pico:  
   - Coloque o Pico em modo de bootloader (segurando o botão BOOTSEL enquanto conecta o cabo USB).  
   - Copie o arquivo UF2 gerado para o dispositivo montado (normalmente identificado como uma unidade USB).

5. Execução:  
   - Após o upload, o firmware iniciará automaticamente. A temperatura filtrada será exibida no display OLED e também impressa na porta serial.

---

📈 **Resultados esperados ou observados**  
- Exibição da Temperatura:  
  O display OLED mostrará a temperatura em graus Celsius, calculada a partir do sensor interno do Pico e filtrada por uma média móvel de 50 amostras. O valor exibido será um número inteiro, evidenciando a estabilidade da medição após a filtragem.
- Leituras no Serial Monitor:  
  Além da exibição no display, o mesmo valor filtrado é impresso no console serial para monitoramento.

