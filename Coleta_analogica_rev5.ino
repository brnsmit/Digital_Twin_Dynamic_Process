//------------------------------------------------
// SETUP INICIAL
//------------------------------------------------

// Inclui bibliotecas necessárias
#include <OneWire.h>
#include <DallasTemperature.h>

// O fio de dados dos sensores de temperatura devem estar conectados à porta 2 do Arduino
// O fio de acionamento do PWM deve estar conectado à porta 5 do Arduino
#define ONE_WIRE_BUS 2
#define PWM_BUS 5

//Ajusta a resolução do sensor de temperatura em bits
#define TEMPERATURE_PRECISION 12

// Definição de constantes de comunicação
const int HANDSHAKE = 0;
const int DATA_REQUEST = 1;
const int ON_REQUEST = 2;
const int STREAM = 3;

// Definição de variáveis
long loop_timer_now;          // tempo atual (em milissegundos)
long previous_millis;         // tempo anterior (em milissegundos)
long loop_time;               // tempo do loop
int value = 0;                // variável com o valor da leitura
int inByte = 0;               // variável de comunicação
int daqMode = ON_REQUEST;     // status da comunicação
int numeroInteiro = 0;        // armazena o valor inteiro da temperatura para poder usar no calculo de limite de temperatura
int dutyCycle = 0;            // armazena o valor da saida pwm

// Parâmetros do modelo: **Parametros editaveis**
int tempMax = 105;            // limite de temperatura em ºC
unsigned long tempRamp = 5000;  // tempo de alteração de saída PWM em ms
int pwmMax = 100;             // valor máximo assumido pelo PWM

// Definição de portas físicas do Arduino
const int pin_pwm = 5;              // pino analógico

// Configura uma instância oneWire para comunicar com dispositivos OneWire (não apenas ICs de temperatura Maxim/Dallas)
OneWire oneWire(ONE_WIRE_BUS);

// Passe nossa referência oneWire para Dallas Temperature.
DallasTemperature sensors(&oneWire);

// Arrays para armazenar endereços dos dispositivos
DeviceAddress mos_Thermometer, amb_Thermometer;

void init_sensors(void)
{
    // Inicia a biblioteca
  sensors.begin();

  // Localiza dispositivos no barramento
  Serial.print("Localizando dispositivos...");
  Serial.print("Encontrado ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" dispositivos.");

  // Reporta os requisitos de energia parasita
  Serial.print("Energia parasita está: ");
  if (sensors.isParasitePowerMode()) Serial.println("LIGADA");
  else Serial.println("DESLIGADA");

  // Método 1: por índice
  if (!sensors.getAddress(mos_Thermometer, 0)) Serial.println("Não foi possível encontrar o endereço do Dispositivo 0");
  if (!sensors.getAddress(amb_Thermometer, 1)) Serial.println("Não foi possível encontrar o endereço do Dispositivo 1");

  // Mostra os endereços encontrados no barramento
  Serial.print("Endereço do Dispositivo 0: ");
  printAddress(mos_Thermometer);
  Serial.println();
  Serial.print("Endereço do Dispositivo 1: ");
  printAddress(amb_Thermometer);
  Serial.println();

  // Configura a resolução para 12 bits por dispositivo
  sensors.setResolution(mos_Thermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(amb_Thermometer, TEMPERATURE_PRECISION);
  Serial.print("Resolução do Dispositivo 0: ");
  Serial.print(sensors.getResolution(mos_Thermometer), DEC);
  Serial.println();
  Serial.print("Resolução do Dispositivo 1: ");
  Serial.print(sensors.getResolution(amb_Thermometer), DEC);
  Serial.println();
}

// Função para imprimir um endereço de dispositivo
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // Completa com zero se necessário
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

// Função para imprimir a resolução de um dispositivo
void printResolution(DeviceAddress deviceAddress)
{
  Serial.print("Resolução: ");
  Serial.print(sensors.getResolution(deviceAddress));
  Serial.println();
}

// Inicialização do código
void setup() {
  Serial.begin(115200);           // inicia a serial
  init_sensors();
  loop_timer_now = millis();
}

//Funções

float get_temp(DeviceAddress deviceAddress)
{
  sensors.requestTemperatures();
  delay(1);
  float tempC = sensors.getTempC(deviceAddress);
  if (tempC == DEVICE_DISCONNECTED_C) 
  {
    Serial.println("Erro: Não foi possível ler os dados de temperatura");
    return;
  }
  return tempC;
}

// Função para imprimir a temperatura para um dispositivo
void printData()
{
  numeroInteiro = int(get_temp(mos_Thermometer));
  loop_timer_now = millis();
  loop_time = loop_timer_now - previous_millis;
  if (numeroInteiro > tempMax){
  dutyCycle = 0;
  analogWrite(pin_pwm, dutyCycle);
  }
  else if (loop_time > tempRamp){
    dutyCycle = random(0, pwmMax);
    analogWrite(pin_pwm, dutyCycle);
    previous_millis = loop_timer_now;
  }
    // escreve o resultado
  if (Serial.availableForWrite()) {
    String outstr = String(String(loop_timer_now, DEC) + "," + int(dutyCycle) + "," + float(get_temp(amb_Thermometer)) + "," + float(get_temp(mos_Thermometer)));
    Serial.println(outstr);
  }
}

//----------------------------------------------
//CÓDIGO
//----------------------------------------------
void loop() {

  // Se está transferindo dados continuamente (modo de streaming)
  if (daqMode == STREAM) {
    printData();   
    }
  // Checa se algum dado foi enviado ao Arduino e responde de acordo
  if (Serial.available() > 0) {
    // Lê sob demanda
    inByte = Serial.read();
    // Handshake
    if (inByte == HANDSHAKE){
      if (Serial.availableForWrite()) {
          Serial.println("Mensagem de handshake recebida.");
      }
    }
    // Se os dados estão sendo solicitados, coleta e escreve
    else if (inByte == DATA_REQUEST) printData();
    // Modifica o modo de aquisição
    else if (inByte == ON_REQUEST) daqMode = ON_REQUEST;
    else if (inByte == STREAM) {daqMode = STREAM;}
  }
}
