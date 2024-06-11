# Desenvolvimento de um Digital Twin para Planta de simulação de um processo de Dinâmico

Este trabalho visa desenvolver um Digital Twin para um processo dinâmico, com o intuito de proporcionar uma representação virtual precisa e em tempo real do referido processo. O objetivo é explorar e implementar técnicas avançadas de modelagem e simulação de sistemas dinâmicos para criar um modelo digital que reflita o comportamento dinâmico do sistema em questão. Além disso, busca-se investigar e aplicar estratégias de integração de dados em tempo real para garantir que o Digital Twin permaneça seja capaz de fornecer informações relevantes para tomada de decisões.

1) Planta de Simulação

Foi desenvolvido uma planta de simulação a qual seu funcionamento baseia-se na interação entre Arduíno Uno e os sensores de temperatura 18B20, com intuito de simular e monitorar um processo dinâmico. No Arduíno foi implementado a técnica de modulação por largura de pulso (PWM) para controlar a carga conectada à placa XY-MOS. A cada 5 minutos, o valor do PWM é ajustado de forma randômica, permitindo variações na saída e, consequentemente, na temperatura de carga. Os sensores de temperatura 18B20, posicionados para medir a temperatura ambiente e da carga, transmitem continuamente os dados ao Arduíno.

 ![image](https://github.com/brnsmit/Digital_Twin_Dynamic_Process/assets/137723215/04baa52f-7e5e-471d-bf4e-b0cd18aac3e9)


2) Banco de Dados

O banco de dados gerado através da planta de simulação e coletado por meio de um código em Python. Esses mesmos dados são coletados e registrados em intervalos regulares, proporcionando insights valiosos para a criação de um modelo de predição de temperatura da planta.


![image](https://github.com/brnsmit/Digital_Twin_Dynamic_Process/assets/168189996/320aa0b5-37e4-4b0e-8cfc-1c7782d0f27f)

- Back-End (Modelo em Python)

O modelo desenvolvido para a previsão foi baseado em LSTM e está disponível em [DigitalTwinV8.ipynb](https://github.com/brnsmit/Digital_Twin_Dynamic_Process/blob/main/DigitalTwinV8.ipynb).

- Front-End

Para visualização do sistema funcionando on-line, acesse:

   
