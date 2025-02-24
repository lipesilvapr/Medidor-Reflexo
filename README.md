# Medidor de Reflexos

## Descrição
O **Medidor de Reflexos** é um sistema embarcado desenvolvido na plataforma BitDogLab para medir o tempo de reação de um usuário a um estímulo visual. O sistema utiliza um LED para indicar o momento de resposta e registra o tempo necessário para que o usuário pressione um botão, exibindo o resultado em um display OLED.

## Objetivos
- Criar um dispositivo eficiente para medir o tempo de reação de uma pessoa.
- Utilizar componentes embarcados como LEDs, botões e um display OLED.
- Aplicar o projeto em testes médicos, avaliações cognitivas e treinamento esportivo.

## Componentes Utilizados
- **Microcontrolador BitDogLab**
- **LEDs (Verde, Azul, Vermelho)**
- **Botão de Entrada (Botão A)**
- **Display OLED (I2C)**
- **Conexão I2C para comunicação com o display**

## Funcionamento
1. O dispositivo exibe "Aguarde..." no display OLED e aguarda um intervalo aleatório (entre 1 e 5 segundos).
2. O LED verde acende para indicar que o usuário deve pressionar o botão o mais rápido possível.
3. O tempo de reação é calculado e exibido no display.
4. Após a exibição do resultado, o sistema aguarda 3 segundos e reinicia o processo.

## Aplicações
- **Medicina**: Avaliação de reflexos neurológicos e detecção precoce de doenças.
- **Psicologia**: Estudos sobre reflexos em diferentes estados emocionais.
- **Segurança Ocupacional**: Testes para motoristas, pilotos e operadores de máquinas.
- **Esportes**: Treinamento e monitoramento da velocidade de reação de atletas.

## Instalação e Uso
### Requisitos
- Placa BitDogLab
- Biblioteca SSD1306 para controle do display OLED
- Configuração do I2C para comunicação com o display

### Compilação e Execução
1. Clone o repositório:
   ```bash
   git clone https://github.com/lipesilvapr/Medidor-Reflexo.git
   ```
2.  Conecte o hardware e inicie o programa.


## Testes e Resultados
Os testes realizados mostraram que os tempos de reação médios por idade foram:
- **18-25 anos**: 190-200ms.
- **40-50 anos**: 373-444ms.
- **60+ anos**: 500ms ou mais.

Esses dados indicam a influência da idade sobre os reflexos e demonstram a viabilidade do sistema para avaliações.
