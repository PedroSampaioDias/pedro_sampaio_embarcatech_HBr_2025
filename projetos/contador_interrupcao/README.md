# 📘 Nome do Projeto

**Contador Decrescente com Registro de Cliques via Interrupção**

---

🎯 **Objetivo do projeto**  
Demonstrar o uso de interrupções em sistemas embarcados para implementar um contador decrescente com registro de cliques. O projeto reinicia a contagem ao pressionar o Botão A, enquanto o Botão B registra cliques durante a contagem, os quais são exibidos em um display OLED.

---

🧩 **Componentes usados**  
- **Microcontrolador:** Raspberry Pi Pico  
- **Display:** OLED com driver SSD1306  
- **Botões:**  
  - **Botão A (GPIO5):** Reinicia a contagem para 9 e zera os cliques do Botão B.  
  - **Botão B (GPIO6):** Registra os cliques durante a contagem regressiva.  
- **Bibliotecas e Recursos:**  
  - Pico SDK  
  - Biblioteca SSD1306 para comunicação I2C com o display OLED  
  - Funções para gerenciamento de interrupções e debounce

---

⚡ **Pinagem dos dispositivos**  
- **Botão A (GPIO5):**  
  - Função: Reinicia a contagem decrescente para 9 e ativa o modo de contagem.  
- **Botão B (GPIO6):**  
  - Função: Conta os cliques durante a contagem regressiva e exibe o total no display OLED.  
- **Display OLED:**  
  - **SDA:** Conectado ao GPIO14  
  - **SCL:** Conectado ao GPIO15

---

🧪 **Como compilar e executar**  
1. **Pré-requisitos:**  
   - Ambiente de desenvolvimento configurado para o Raspberry Pi Pico com o Pico SDK instalado.  
   - Instalação das bibliotecas necessárias para o display OLED (SSD1306) e suporte ao I2C.

2. **Compilação:**  
   - Crie um diretório para compilação e acesse-o:
     ```bash
     mkdir build && cd build
     ```  
   - Configure o projeto com CMake:
     ```bash
     cmake ..
     ```  
   - Compile o projeto:
     ```bash
     make
     ```  

3. **Deploy e Execução:**  
   - Conecte o Raspberry Pi Pico ao computador e coloque-o em modo de armazenament.  
   - Copie o arquivo UF2 gerado para o dispositivo Pico.  
   - O firmware inicia automaticamente, mostrando a contagem regressiva e os registros de cliques no display OLED.

---

📈 **Resultados esperados ou observados**  
- **Resultado Esperado:**  
  - Ao pressionar o Botão A, o contador inicia a contagem regressiva a partir de 9, decrementando a cada segundo até 0.  
  - Durante a contagem, os pressionamentos do Botão B são contabilizados e exibidos em tempo real.  
  - Quando o contador atinge 0, o sistema congela, exibindo 0 e o total de cliques, ignorando novos pressionamentos do Botão B até nova reinicialização.
  
- **Resultado Observado:**  
  - O display OLED mostra dinamicamente o valor do contador e a quantidade de cliques acumulados do Botão B.  
  - O sistema reinicia corretamente o processo quando o Botão A é pressionado, reiniciando o contador para 9 e zerando os cliques.

---

### Explicação da Lógica da Tarefa

O programa implementa um contador decrescente com controle por interrupção, seguindo estes pontos principais:

- **Interrupção do Botão A:**  
  - Ao pressionar o Botão A (GPIO5), uma interrupção é acionada que:  
    - Reinicializa o contador para 9.  
    - Zera o contador de cliques do Botão B.  
    - Atualiza o display OLED com os novos valores.  
    - Inicia a contagem regressiva.

- **Contagem Decrescente:**  
  - Um temporizador decrementa o valor do contador de 9 até 0, atualizando o display a cada segundo.  
  - Durante o processo, o display mostra simultaneamente o valor corrente do contador e os cliques acumulados do Botão B.

- **Registro dos Cliques do Botão B:**  
  - Pressionamentos do Botão B (GPIO6) durante a contagem são registrados e incrementados, e o total é exibido junto ao contador.

- **Finalização da Contagem:**  
  - Quando o contador chega a 0, o sistema "congela" a contagem, exibindo 0 e o total final de cliques, ignorando novos pressionamentos do Botão B até que o Botão A seja pressionado novamente para reiniciar o processo.
