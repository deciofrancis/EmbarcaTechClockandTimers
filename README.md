## 🔥 Projeto: Clock e Temporizadores

## 📌 Descrição do Projeto

Este repositório contém a implementação de dois sistemas utilizando o Raspberry Pi Pico W com o Pico SDK:

1. **Temporizador Periódico:** Um semáforo com ciclos automáticos de 3 segundos.

2. **Temporizador de Um Disparo (One Shot):** Um sistema de temporização ativado por um botão.

## 1. Temporizador Periódico (Semáforo)

## 🛠️ Componentes Utilizados

- **Raspberry Pi Pico W**
- **03 LEDs (Vermelho, Amarelo e Verde)**
- **03 Resistores de 330 Ω** 

## 📋 Requisitos:

1. O acionamento dos LEDs inicia na cor vermelha, depois muda para amarela e, em seguida, verde.

2. O temporizador deve ser ajustado para um atraso de 3 segundos (3.000ms) entre cada troca de cor.

3. A mudança de estado dos LEDs é implementada na função de call-back do temporizador (repeating_timer_callback).

4. A rotina principal (while) imprime uma mensagem na porta serial a cada 1 segundo (1.000ms).

5. Simulação com a ferramenta BitDogLab utilizando o LED RGB (GPIOs 11, 12 e 13).

## 2. Temporizador de Um Disparo (One Shot)

## 🛠️ Componentes Utilizados

- **Raspberry Pi Pico W**
- **03 LEDs (Vermelho, Amarelo e Verde)**
- **03 Resistores de 330 Ω** 
- **01 Botão (Pushbutton)** 

## 📋 Requisitos:

1. Ao pressionar o botão:
    - Os três LEDs são acionados (estado alto).
    - Após 3 segundos, um LED é desligado.
    - Após mais 3 segundos, outro LED é desligado.
    - Após mais 3 segundos, o último LED é desligado.

2. O temporizador é baseado na função add_alarm_in_ms().

3. A mudança de estado dos LEDs é implementada em funções de call-back (turn_off_callback).

4. O botão só pode iniciar uma nova chamada após o último LED ser desligado.

5. Simulação com BitDogLab utilizando LED RGB (GPIOs 11, 12 e 13) e Botão A (GPIO 05).

6. (Opcional) Implementação de software debounce para evitar efeito bouncing do botão.


## 🛠️ Configurando o Projeto no VS Code

1. **Clonar o Repositório**:
```
git clone https://github.com/deciofrancis/EmbarcaTechClockandTimers
cd EmbarcaTechClockandTimers
```

2. **Pra o primeiro projeto - Abra o VS Code** e **importe o projeto**:
   - Vá até a **Extensão Raspberry Pi Pico**.
   - Selecione **Import Project**.
   - Escolha a pasta do repositório clonado.
   - Clique em **Import**.

3. **Compilar o código**:
   - Utilize a opção de **Build** da extensão.

4. **Rodar no BitDogLab**:
   - Na extensão do VSCode Raspberry PI PICO Project.
   - Clique em **Run Project(USB)** para enviar o arquivo para a BitDogLab.

5. **Pra o segundo projeto**
```
cd OneShot
```

6. **Compilar o código**:
   - Utilize a opção de **Build** da extensão.

7. **Rodar no BitDogLab**:
   - Na extensão do VSCode Raspberry PI PICO Project.
   - Clique em **Run Project(USB)** para enviar o arquivo para a BitDogLab.


## Desenvolvedor

[Décio Francis](https://www.linkedin.com/in/deciofrancis/)