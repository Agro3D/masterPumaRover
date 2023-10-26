#ifndef common_H
#define common_H


// Essse Arquivo contém os include das bibliotecas utilizadas no projeto,
// as definições de constantes, as variáveis globais e as inicializações das funções


using namespace std;


// Bibliotecas Utilizadas no Programa
#include <Arduino.h>                                        // Biblioteca padrão do Arduino
#include <ArduinoJson.h>                                    // Biblioteca para manipular objetos JSON
#include <AsyncJson.h>                                      // Biblioteca para manipular requisições HTTP JSON assíncronas
#include <ESPAsyncWebServer.h>                              // Biblioteca para criar servidor web assíncrono
#include <WebSocketsServer.h>                               // Biblioteca para criar servidor web socket
#include <WiFi.h>                                           // Biblioteca para operações de WiFi
#include <bits/stdc++.h>                                    // Biblioteca para manipular arrays
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>           // Biblioteca do GNSS
#include <esp_ipc.h>



// Constantes de configuração do sistema
#define DEBUG true                                         // Variável para habilitar/desabilitar o envio de mensagens para o monitor serial

#define ZED_COMM_SPEED 460800                              // Velocidade de comunicação com o ZED
#define ESP_COMM_SPEED 921600                              // Velocidade de comunicação com o ZED

#define MYPORT_RX 18                                        // Porta recepção UART
#define MYPORT_TX 17                                        // Porta transmissão UART

#define STACK_SIZE_CPU 2048                                 // Tamanho da pilha dos processos de cada core

#define HEAP_SIZE_TIMER 300000                              // Intervalo de tempo para enviar o status do heap para o escravo, em milisegundos

#define SERVER_PORT 80                                      // Porta do servidor HTTP

#define SEND_DATA_TRIES 5                                   // Número de tentativas de envio de dados para o escravo

#define MARGEM_COTA_REFERENCIA 10                           // Margem de erro para a cota de referência, em centímetros(100cm = 1M)


// Botões de ligar/desligar o sistema
#define POWER_CHECK 5                                       // Pino do botão liga/desliga
#define POWER_OFF 6                                         // Pino para ligar/desligar o sistema
#define POWER_TIMER 2000                                    // Tempo de pressionar o botão para ligar/desligar para desligar o sistema, em milisegundos


// Constantes para identificar o tipo de mensagem enviada para o escravo
#define INICIALIZAR 0                                       // Mensagem para informar que o mestre está inicializando

#define NOVO_TRABALHO 1                                     // Mensagem para enviar uma nova configuração para o escravo
#define RESP_NOVO_TRABALHO 2                                // Mensagem para receber a resposta do escravo sobre a configuração

#define PARAR_TRABALHO 3                                    // Mensagem para cancelar a pesquisa realizada pelo escravo
#define RESP_PARAR_TRABALHO 4                               // Mensagem para receber a resposta do escravo sobre o cancelamento da pesquisa

#define NOVO_PONTO 5                                        // Mensagem para salvar um novo ponto de interesse
#define RESP_NOVO_PONTO 6                                   // Mensagem para receber a resposta do escravo sobre o salvamento do ponto de interesse

#define LISTAR_ARQUIVOS 7                                   // Mensagem para listar os arquivos salvos no escravo
#define RESP_LISTAR_ARQUIVOS 8                              // Mensagem para receber a resposta do escravo sobre a listagem dos arquivos

#define LISTAR_PONTOS 9                                     // Mensagem para listar os pontos de interesse salvos no escravo
#define RESP_LISTAR_PONTOS 10                               // Mensagem para receber a resposta do escravo sobre a listagem dos pontos de interesse


#define ALERT_MESSAGE 90                                    // Mensagem para mostrar um alerta no servidor


#define SINAL_RADIO 95                                   // Mensagem para receber o status do sinal de rádio do escravo

#define GET_STATUS 98                                       // Mensagem para solicitar o status do escravo
#define ACK_MSG 99                                          // Mensagem de confirmação de comunicação com o escravo

#define HEAP_SIZE 100                                       // Mensagem de enviar o tamanho da heap do mestre


// Definições de Status
#define ESPERANDO 0
#define TRABALHANDO 1




// Variáveis Globais
char ssid[] = "PumaRover";                                  // nome do AP
char password[] = "00000000";                               // senha do AP

// Variaveis para teste de armazenamento de dados nos nucleos
TaskHandle_t taskCommHandler, taskProcessHandler;           // Variáveis para armazenar o handle das tasks

HardwareSerial MySerialZed(0);                              // Use UART0
AsyncWebServer server(SERVER_PORT);                         // Cria o servidor web na porta 80
WebSocketsServer webSocket = WebSocketsServer(81);          // Cria o servidor web socket na porta 81
HardwareSerial MySerial(1);                                 // Use the 2nd hardware serial port. 0 is connected to the USB
bool hasComunication = false;                               // Flag para controlar se a comunicação com o escravo está estabelecida
bool serverStarted = false;                                 // Flag para controlar se o servidor web está iniciado
bool receberMensagens = false;                              // Flag para controlar o recebimento de mensagens do escravo
unsigned long lastHeapSend = 0;                             // Variável para armazenar o tempo da última verificação do heap

bool sinalRadio = true;                                     // Flag para controlar o sinal de rádio

String mensagemStr;                                         // String para armazenar a representação em texto do objeto JSON
String heapSize;                                            // String para armazenar o tamanho da heap do mestre
vector<String> listaMensagens;                              // Lista de mensagens referentes aos comandos enviados para o escravo
String listaArquivosStr="";                                 // String para armazenar a lista de arquivos do escravo
StaticJsonDocument<30720> listaPontos;                      // Iniciar o objeto JSON

String cota;                                                // Variável para armazenar o valor da cota atual
char RTKAtual = '-1';                                       // Variável para armazenar o valor do status atual do RTK
String precisaoVertical = "-1";                             // Variável para armazenar o valor da precisão vertical
String precisaoHorizontal = "-1";                           // Variável para armazenar o valor da precisão horizontal

float cotaRef = FLT_MIN;                                    // Variável para armazenar o valor da cota de referência
float cotaRefInferior = FLT_MIN;                            // Variável para armazenar o valor da cota de referência inferior
float cotaRefSuperior = FLT_MIN;                            // Variável para armazenar o valor da cota de referência superior
char statusAtual;                                           // Variável para armazenar o status atual do escravo

int comandoEscravo = -1;                                    // Flag para controlar o envio de dados para o escravo
vector<int> listaComandos;                                  // Lista de comandos para o escravo
bool waitResponse = false;                                  // Flag para controlar o recebimento de dados do escravo
bool verifyingComunication = false;                         // Flag para controlar a verificação de comunicação com o escravo

int timerBotao = 0;                                         // Variável para armazenar o tempo de pressionamento do botão de ligar/desligar


// Lista de todas as funções do programa
void getStatus(String mensagem);
void setupServer();
void setupServerPages();
void setupServerScripts();
void setupServerStyles();
void slaveReceiveHandler();
String slaveReceiveResponse();
void slaveSendData(String data);
void slaveSendHandler();
bool verifyComunication();
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);
void processaMensagem(String message);
void processaNMEAGGA(String nmeastr);
void processaNMEAPUBX(String pubxstr);
void listarPontos(String resposta);
void printString(String message);
void printJson(DynamicJsonDocument doc);
void printStringNoBreak(String message);
void novoPonto(String Ponto);
void novoComando(int novoComando, String novaMensagem);
void proximoComando();
void printListaComandos();
void printFuncCore(String func);




// Includes dos módulos do programa

// Páginas do servidor web
#include "../server/header.h"               // Cabeçalho da página do servidor web
#include "../server/index.h"                // Página principal
#include "../server/arquivos.h"             // Página arquivo


// Estilos CSS do servidor web
#include "../server/globalStyle.h"          // Estilo CSS global do servidor web
#include "../server/headerStyle.h"          // Estilo CSS do cabeçalho das páginas do servidor web
#include "../server/sinalRadioStyle.h"      // Estilo CSS das torres de sinal do rádio
#include "../server/indexConfigStyle.h"     // Estilo CSS da página principal (configuração)
#include "../server/indexStatusStyle.h"     // Estilo CSS da página principal (status)
#include "../server/listaPontosStyle.h"     // Estilo CSS da lista de pontos
#include "../server/popupStyle.h"           // Estilo CSS do popup de novo ponto
#include "../server/arquivosStyle.h"        // Estilo CSS da página arquivos


// Scripts JS do servidor web
#include "../server/globalScript.h"         // Script JS global do servidor web
#include "../server/indexConfigScript.h"    // Script JS da página principal (configuração)
#include "../server/indexStatusScript.h"    // Script JS da página principal (status)
#include "../server/pontosScript.h"         // Script JS da página arquivos
#include "../server/webSocketScript.h"      // Script JS do webSocket


// Funções do Programa
#include "server.h"                         // Funções do servidor web
#include "serverPages.h"                    // Funções das páginas do servidor web
#include "serverStyles.h"                   // Funções dos estilos CSS do servidor web
#include "serverScripts.h"                  // Funções dos scripts JS do servidor web

#include "requestHandler.h"                 // Funções de comunicação com o escravo
#include "responseHandler.h"                // Funções do servidor web socket

#include "dualCoreHandler.h"                // Funções de comunicação com o escravo
#include "zedHandler.h"                     // Funções de comunicação com o escravo
#include "utils.h"                          // Funções de utilidades


#endif