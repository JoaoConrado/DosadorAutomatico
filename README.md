Dosador Automático com Fichas (Arduino)

📖 Sobre o Projeto
Este é um projeto de um Dosador Automático de Líquidos controlado por um Arduino. O sistema foi projetado para operar com fichas: o usuário insere uma ou mais fichas para definir a quantidade de doses desejada, e a máquina dispensa a quantidade exata de líquido, medindo o peso em tempo real com uma célula de carga.

A interação com o usuário é feita através de um display LCD 16x2, que guia por todas as etapas do processo, desde a inserção das fichas até a retirada do copo. O projeto também inclui sensores para garantir a operação segura, como um sensor de nível para o reservatório de líquido.

🛠️ Componentes Utilizados
Eletrônicos
Placa: Arduino Uno (ou compatível)

Display: Módulo LCD 16x2 com interface I2C ou paralela

Sensor de Peso: Célula de Carga + Módulo Amplificador HX711

Atuadores:

1x Micro Servo Motor (para o mecanismo de fichas)

1x Mini Bomba de Líquido

Entradas de Usuário:

1x Push Button (Botão de pulso)

1x Mecanismo de Ficheiro/Moedeiro (conectado a um pino de interrupção)

Sensores:

1x Sensor de Nível de Líquido

Sinalização:

5x LEDs (para indicar a quantidade de doses)

Resistores apropriados para os LEDs

Bibliotecas Arduino
Servo.h

LiquidCrystal.h

HX711.h

📍 Diagrama de Conexões (Pinagem)
Componente

Pino no Arduino

Moedeiro (Interruptor)

2

Sensor de Nível

3

HX711 (DT)

4

HX711 (SCK)

5

Servo Motor

6

Botão de Avançar

7

Bomba de Líquido

8

LED 1

9

LED 2

10

LED 3

11

LED 4

12

LED 5

13

LCD (RS, E, D4, D5, D6, D7)

14, 15, 16, 17, 18, 19

🚀 Funcionalidades
Operação por Fichas: O número de doses é definido pela quantidade de fichas inseridas.

Dosagem por Peso: Utiliza uma célula de carga para garantir uma dosagem precisa do líquido.

Interface Guiada: Um display LCD informa o usuário sobre cada passo a ser seguido.

Controle de Nível: Um sensor monitora o reservatório e avisa quando o líquido está acabando.

Sinalização Visual: LEDs indicam o número de doses selecionadas.

Detecção de Copo: O sistema aguarda o usuário posicionar o copo na balança antes de iniciar a dosagem.

Máquina de Estados: O fluxo de operação é controlado por uma máquina de estados robusta, garantindo que os passos ocorram na ordem correta.

⚙️ Como Funciona (Fluxo de Operação)
Inicialização: O LCD exibe uma mensagem de boas-vindas. O sistema aguarda o primeiro comando.

Liberação do Ficheiro: O usuário aperta o botão, o servo motor abre a passagem para as fichas.

Seleção de Doses: O usuário insere as fichas. Para cada ficha, um LED acende e o contador de doses (c) é incrementado. Após 5 fichas, o mecanismo é travado.

Confirmação: O sistema fecha o ficheiro e pede para o usuário apertar o botão para confirmar.

Posicionamento do Copo: O LCD instrui o usuário a colocar o copo na balança. O sistema só avança após detectar o peso do copo.

Início da Dosagem: O usuário aperta o botão para iniciar o processo.

Dosagem: A bomba é acionada. O sistema mede o peso do líquido em tempo real e desliga a bomba quando o peso total ( pesoDose * c ) é atingido.

Retirada do Copo: O sistema avisa que a dosagem terminou e aguarda a retirada do copo (detectada pela diminuição do peso).

Finalização: Uma mensagem de agradecimento é exibida e o sistema retorna ao estado inicial, pronto para o próximo cliente.

🔧 Instalação e Upload
Instale a IDE do Arduino: Baixe e instale a Arduino IDE em seu computador.

Instale as Bibliotecas:

Na Arduino IDE, vá em Sketch > Include Library > Manage Libraries....

Procure e instale as seguintes bibliotecas:

HX711 (procure por "HX711 Arduino Library by bodge")

As bibliotecas Servo e LiquidCrystal geralmente já vêm instaladas com a IDE.

Calibração da Balança:

Antes de usar o código final, é crucial calibrar a sua célula de carga. Use um sketch de calibração da biblioteca HX711 para encontrar o valor correto para scale.set_scale().

Atualize a linha scale.set_scale(341800); com o seu valor de calibração.

Upload do Código:

Conecte sua placa Arduino ao computador.

Selecione a placa e a porta correta em Tools.

Clique no botão de Upload para enviar o código para a placa.

📝 Licença
Este projeto está sob a licença MIT.

📧 Contato
João Conrado

Email: joaolucasc@ucl.br

GitHub: https://github.com/JoaoConrado
