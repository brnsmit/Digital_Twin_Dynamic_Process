# Desenvolvimento de um Digital Twin para Planta de simulação de um processo de Dinâmico

Este trabalho visa desenvolver um Digital Twin para um processo dinâmico, com o intuito de proporcionar uma representação virtual precisa e em tempo real do referido processo. O objetivo é explorar e implementar técnicas avançadas de modelagem e simulação de sistemas dinâmicos para criar um modelo digital que reflita o comportamento dinâmico do sistema em questão. Além disso, busca-se investigar e aplicar estratégias de integração de dados em tempo real para garantir que o Digital Twin permaneça seja capaz de fornecer informações relevantes para tomada de decisões.

- Planta de Simulação

Foi desenvolvido uma planta de simulação a qual seu funcionamento baseia-se na interação entre Arduíno Uno e os sensores de temperatura 18B20, com intuito de simular e monitorar um processo dinâmico. No Arduíno foi implementado a técnica de modulação por largura de pulso (PWM) para controlar a carga conectada à placa XY-MOS. A cada 5 minutos, o valor do PWM é ajustado de forma randômica, permitindo variações na saída e, consequentemente, na temperatura de carga. Os sensores de temperatura 18B20, posicionados para medir a temperatura ambiente e da carga, transmitem continuamente os dados ao Arduíno.

 ![image](https://github.com/brnsmit/Digital_Twin_Dynamic_Process/assets/168189996/b06568a8-af7b-4e8f-8b3f-81282748b0ef)

- Banco de Dados

O banco de dados gerado através da planta de simulação e coletado por meio de um código em Python, esses mesmos dados são coletados e registrados em intervalos regulares, proporcionando insights valiosos para a criação de um modelo de predição de temperatura da planta.

![image](https://github.com/brnsmit/Digital_Twin_Dynamic_Process/assets/137723215/fbad7413-4469-4d67-a561-2c6397164ba3)

![image](https://github.com/brnsmit/Digital_Twin_Dynamic_Process/assets/168189996/320aa0b5-37e4-4b0e-8cfc-1c7782d0f27f)

- Back-End (Modelo em Python)

O modelo desenvolvido para a previsão foi baseado em LSTM e está disponível em [DigitalTwinV8.ipynb](https://github.com/brnsmit/Digital_Twin_Dynamic_Process/blob/main/DigitalTwinV8.ipynb).

As principais funções executadas no modelo são:

1. Handshake com Arduino: Reinicializa a conexão, lê e escreve códigos de handshake para sincronização.
2. Parse de Dados do Arduino: Converte bytes recebidos em valores numéricos (tempo, PWM, temperatura ambiente, temperatura MOSFET).
3. Coleta e Processamento de Dados: Envia comando de solicitação de dados e lê a resposta.
4. Armazenamento de Dados em CSV: Salva os dados coletados em um arquivo CSV.
5. Modelos de Previsão: Carrega um modelo pré-treinado (LSTM, etc.) a partir de um arquivo.
6. Previsão com Dados: Usa os dados coletados para fazer previsões utilizando o modelo carregado.
7. Comunicação MQTT: Publica os dados coletados/previsões em um tópico MQTT.
8. Execução do Script: Realiza handshake, coleta dados, salva em CSV, carrega modelo, faz previsões, publica resultados via MQTT.

- Front-End

O TagoIO é uma plataforma de Internet das Coisas (IoT) que simplifica a coleta, visualização e análise de dados vindos de dispositivos conectados. Com ferramentas especializadas, auxilia desenvolvedores e empresas na gestão eficiente de seus dados de IoT.

![image](https://github.com/brnsmit/Digital_Twin_Dynamic_Process/assets/137723215/204c99c6-0def-405a-a159-20751a177e39)


Para visualização do sistema funcionando on-line, acesse: [Shadow Twin](https://664fcaa10f613300098d3dea.tago.run/dashboards/info/66560ec70f6133000927f7c4?anonymousToken=00000000-664f-caa1-0f61-3300098d3dea).

