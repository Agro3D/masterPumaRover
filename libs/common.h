#ifndef common_H
#define common_H


// Essse Arquivo contém os include das bibliotecas utilizadas no projeto,
// as definições de constantes, as variáveis globais e as inicializações das funções



// Bibliotecas Utilizadas no Programa
#include <Arduino.h>                                        // Biblioteca padrão do Arduino
#include <ArduinoJson.h>                                    // Biblioteca para manipular objetos JSON
#include <AsyncJson.h>                                      // Biblioteca para manipular requisições HTTP JSON assíncronas
#include <ESPAsyncWebServer.h>                              // Biblioteca para criar servidor web assíncrono
#include <WebSocketsServer.h>                               // Biblioteca para criar servidor web socket
#include <WiFi.h>                                           // Biblioteca para operações de WiFi



// Constantes de configuração do sistema
#define SERVER_PORT 80                                      // Porta do servidor HTTP
#define CHUNK_SIZE 64                                       // Tamanho do chunk de dados enviado para o escravo
#define SEND_DATA_TRIES 5                                   // Número de tentativas de envio de dados para o escravo
#define RECEIVE_DATA_TRIES 5                                // Número de tentativas de recebimento de dados do escravo
#define MYPORT_RX 18                                        // Porta recepção UART
#define MYPORT_TX 17                                        // Porta transmissão UART
#define DEBUG true                                         // Variável para habilitar/desabilitar o envio de mensagens para o monitor serial
#define MARGEM_COTA_REFERENCIA 10                           // Margem de erro para a cota de referência, em centímetros(100cm = 1M)
#define HEAP_SIZE_TIMER 120000                              // Intervalo de tempo para enviar o status do heap para o escravo, em milisegundos


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

#define GET_PRECISAO 96                                     // Mensagem para solicitar o status do escravo
#define GET_RTKSTATUS 97                                    // Mensagem para solicitar o status do escravo

#define GET_STATUS 98                                       // Mensagem para solicitar o status do escravo
#define ACK_MSG 99                                          // Mensagem de confirmação de comunicação com o escravo

#define HEAP_SIZE 100                                       // Mensagem de enviar o tamanho da heap do mestre


// Definições de Status
#define ESPERANDO 0
#define TRABALHANDO 1




// Variáveis Globais
char ssid[] = "PumaRover";                                  // nome do AP
char password[] = "00000000";                               // senha do AP

HardwareSerial MySerialZed(0);                              // Use UART0
AsyncWebServer server(SERVER_PORT);                         // Cria o servidor web na porta 80
WebSocketsServer webSocket = WebSocketsServer(81);          // Cria o servidor web socket na porta 81
HardwareSerial MySerial(1);                                 // Use the 2nd hardware serial port. 0 is connected to the USB
bool hasComunication = false;                               // Flag para controlar se a comunicação com o escravo está estabelecida
bool serverStarted = false;                                 // Flag para controlar se o servidor web está iniciado
bool receberMensagens = false;                              // Flag para controlar o recebimento de mensagens do escravo
unsigned long lastHeapSend = 0;                             // Variável para armazenar o tempo da última verificação do heap

String mensagemStr;                                         // String para armazenar a representação em texto do objeto JSON
String mensagemStrAux;                                      // String auxiliar para armazenar a representação em texto do objeto JSON
String listaArquivosStr="";                                 // String para armazenar a lista de arquivos do escravo
String listaPontos="";                                      // String para armazenar a lista de pontos do arquivo

int RTKAtual = -1;                                          // Variável para armazenar o valor da pressão atual do RTK
int precisaoRTK = -1;                                       // Variável para armazenar o valor da pressão de precisão do RTK
float cotaRefInferior = -1;                                 // Variável para armazenar o valor da cota de referência inferior
float cotaRefSuperior = -1;                                 // Variável para armazenar o valor da cota de referência superior
char statusAtual;                                           // Variável para armazenar o status atual do escravo

int comandoEscravo = -1;                                    // Flag para controlar o envio de dados para o escravo
int proximoComandoEscravo = -1;                             // Flag para controlar o envio de dados para o escravo, Caso ja exista um comando em andamento
bool escravoTrabalhando = false;
bool waitResponse = false;                                  // Flag para controlar o recebimento de dados do escravo
bool verifyingComunication = false;                         // Flag para controlar a verificação de comunicação com o escravo


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
String getAltitudeFromNMEA(String nmea);
void processaMensagem(String message);
void updateRTK(int comando, int valor);
void listarPontos(String resposta);
void printString(String message);
void printJson(DynamicJsonDocument doc);
void printStringNoBreak(String message);
void novoPonto(String nomePonto);



// Includes dos módulos do programa

// Páginas do servidor web
#include "../server/header.h"               // Cabeçalho da página do servidor web
#include "../server/index.h"                // Página principal
#include "../server/arquivos.h"             // Página arquivo


// Estilos CSS do servidor web
#include "../server/globalStyle.h"          // Estilo CSS global do servidor web
#include "../server/headerStyle.h"          // Estilo CSS do cabeçalho das páginas do servidor web
#include "../server/indexConfigStyle.h"     // Estilo CSS da página principal (configuração)
#include "../server/indexStatusStyle.h"     // Estilo CSS da página principal (status)
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

#include "zedHandler.h"                     // Funções de comunicação com o escravo
#include "utils.h"                          // Funções de utilidades


#endif