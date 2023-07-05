#ifndef common_H
#define common_H

// Bibliotecas Utilizadas no Programa
#include <Arduino.h>                    // Biblioteca para manipular objetos JSON
#include <ArduinoJson.h>                // Biblioteca para manipular objetos JSON
#include <AsyncJson.h>                  // Biblioteca para manipular requisições HTTP JSON assíncronas
#include <ESPAsyncWebServer.h>          // Biblioteca para criar servidor web assíncrono
#include <WebSocketsServer.h>           // Biblioteca para criar servidor web socket
#include <WiFi.h>                       // Biblioteca para operações de WiFi


// Constantes do Programa
#define SERVER_PORT 80                  // Porta do servidor HTTP
#define CHUNK_SIZE 64                   // Tamanho do chunk de dados enviado para o escravo
#define SEND_DATA_TRIES 5               // Número de tentativas de envio de dados para o escravo
#define RECEIVE_DATA_TRIES 5            // Número de tentativas de recebimento de dados do escravo
#define MYPORT_RX 18                    // Porta recepção UART
#define MYPORT_TX 17                    // Porta transmissão UART

// Constantes para identificar o tipo de mensagem enviada para o escravo
#define NOVO_TRABALHO 1
#define CANCELAR_TRABALHO 2
#define FINALIZAR_TRABALHO 3

#define CANCELAR_PESQUISA 11
#define PULAR_PESQUISA 12

#define LISTA_ARQUIVOS 21
#define BAIXAR_ARQUIVOS 22
#define EXCLUIR_ARQUIVOS 23


#define GET_STATUS 98                   // Mensagem para verificar o status do trabalho realizado pelo escravo
#define ACK_MSG 99                      // Mensagem de confirmação de comunicação com o escravo


// Definições de Status
#define ESPERANDO 0
#define PESQUISANDO 1
#define PROCESSANDO 2
#define SALVANDO 3


// Variáveis Globais
char ssid[] = "PumaStation2";           // nome do AP
char password[] = "00000000";           // senha do AP

AsyncWebServer server(SERVER_PORT);                     // Cria o servidor web na porta 80
WebSocketsServer webSocket = WebSocketsServer(81);      // Cria o servidor web socket na porta 81
HardwareSerial MySerial(1);                             // Use the 2nd hardware serial port. 0 is connected to the USB
bool hasComunication = false;                            // Flag para controlar se a comunicação com o escravo está estabelecida
bool serverStarted = false;                             // Flag para controlar se o servidor web está iniciado

// JsonObject jsonObj;                             // Objeto JSON para receber dados do cliente
String mensagemStr;                             // String para armazenar a representação em texto do objeto JSON
String listaArquivosStr;                        // String para armazenar a lista de arquivos do escravo
int ComandoEscravo;                             // Flag para controlar o envio de dados para o escravo
bool waitResponse = false;                      // Flag para controlar o recebimento de dados do escravo
bool verifyingComunication = false;             // Flag para controlar a verificação de comunicação com o escravo


// Lista de todas as funções do programa
void excluirArquivos();
void getStatus();
void listaArquivos();
void setupServer();
void setupServerPages();
void setupServerScripts();
void setupServerStyles();
void slaveListerner();
void slaveReceiveHandler();
String slaveReceiveResponse();
void slaveSendData(String data);
void slaveSendHandler();
bool verifyComunication();
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);



// Includes dos módulos do programa

// Páginas do servidor web
#include "../server/header.h"               // Cabeçalho da página do servidor web
#include "../server/index.h"                // Página principal
#include "../server/arquivos.h"             // Página arquivo

// Estilos CSS do servidor web
#include "../server/globalStyle.h"          // Estilo CSS global do servidor web
#include "../server/headerStyle.h"          // Estilo CSS do cabeçalho das páginas do servidor web
#include "../server/indexStyle.h"           // Estilo CSS da página principal
#include "../server/arquivosStyle.h"        // Estilo CSS da página arquivos

// Scripts JS do servidor web
#include "../server/globalScript.h"         // Script JS global do servidor web
#include "../server/indexScript.h"          // Script JS da página principal
#include "../server/arquivosScript.h"       // Script JS da página arquivos
#include "../server/webSocketScript.h"      // Script JS do webSocket


// Funções do Programa
#include "server.h"                         // Funções do servidor web
#include "serverPages.h"                    // Funções das páginas do servidor web
#include "serverStyles.h"                   // Funções dos estilos CSS do servidor web
#include "serverScripts.h"                  // Funções dos scripts JS do servidor web
#include "requestHandler.h"                 // Funções de comunicação com o escravo
#include "responseHandler.h"                // Funções do servidor web socket


#endif