// Variáveis Globais
#include "libs/common.h"                // Variáveis globais


// Função para realizar a configuração inicial do servidor web.
void setup() {
  delay(6000);
  Serial.begin(115200);
  
  // Imprime linhas de separação e mensagens de inicialização no console serial.
  printString("");
  printString("");
  printString("============================================================");
  printString("  ----- Inicializando o Master Puma Rover RTK -----  ");
  // printString("Versao do Arduino: " + String(ARDUINO));


  // Inicia o protocolo UART para comunicação com o escravo.
  printString("");
  printString("Iniciando Comunicação UART (Escravo)");
  MySerial.begin(460800, SERIAL_8N1, MYPORT_RX, MYPORT_TX);     // Set up the hardware serial port
  delay(1000);
  while (MySerial.available()) MySerial.read();

  printString("Comunicação UART (Escravo) Inicializada");



  // Inicia o protocolo UART para comunicação com o ZED.
  printString("");
  printString("Iniciando Comunicação UART (ZED)");
  MySerialZed.begin(460800, SERIAL_8N1, RX, TX);                // Set up the hardware serial port
  delay(1000);
  while (MySerialZed.available()) MySerialZed.read();

  printString("Comunicação UART (ZED) Inicializada");


  // Inicia o WiFi no modo AP com o SSID e a senha definidos.
  printString("");
  printString("Inicializando o WiFi");
  while(!WiFi.softAP(ssid, password)) {
    printString("Falha na configuracao do AP");
    printString("Tentando novamente...");
    delay(1000);
  }


  // Imprime informações sobre o AP no console serial.
  printString("WiFi Inicializado");
  printString("SSID: .................................. " + String(ssid));
  printString("Senha: ................................. " + String(password));
  printString("MAC Address: ........................... " + WiFi.softAPmacAddress());

  IPAddress IP = WiFi.softAPIP();
  printStringNoBreak("Endereco de IP do Access Point: ........ ");
  printString(String(IP));


  // Iniciar o servidor WebSocket
  printString("Inicializando o servidor WebSocket");
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  printString("Servidor WebSocket Inicializado");


  // Inicia o servidor web e imprime uma mensagem no console serial.
  printString("");
  printString("Iniciando o servidor HTTP");
  setupServer();
  server.begin();
  printString("Servidor HTTP iniciado em http://" + String(IP.toString()));


  ComandoEscravo = LISTAR_ARQUIVOS;                 // Envia o comando de lista de arquivos para o escravo.
  slaveSendHandler();                               // Chama a função de manipulação de envio para o escravo.
  slaveReceiveHandler();                            // Chama a função de manipulação de recebimento do escravo.

  statusAtual = char(ESPERANDO);
  listaPontos = "";

  printString("\n\n\tMaster Puma Rover inicializado.");

  printString("");
  printString("============================================================");
  printString("");
  printString("Servidor aguardando requisicoes...");
  printString("");
}


// Função principal do programa
void loop() {
  // Função principal executada repetidamente após a função de inicialização.

  // Verifica se ha alguma requisicao pendente no servidor web, ou alguma mensagem pendente do escravo.
  if(ComandoEscravo || MySerial.available()) {
    slaveSendHandler();                           // Chama a função de manipulação de envio para o escravo.
    slaveReceiveHandler();                        // Chama a função de manipulação de recebimento do escravo.
  }


  // Lê as mensagens recebidas do ZED
  while (MySerialZed.available()) {
    String message = MySerialZed.readStringUntil('\n');

    if(receberMensagens){
      processaMensagem(message);
    }
  }

  static uint32_t lastHeapSize = 0;
  uint32_t currentHeapSize = ESP.getFreeHeap();

  // If the heap size has decreased since the last loop iteration, print a warning
  if (currentHeapSize < lastHeapSize) {
    printStringNoBreak("WARNING: Heap size decreased! Current heap size: ");
    printString(String(currentHeapSize));
  }

  lastHeapSize = currentHeapSize;

  webSocket.loop();
  delay(300);
}


// Função para verificar se a comunicação com o escravo foi estabelecida
bool verifyComunication(){
  printStringNoBreak("Verificando a conexao com o escravo...");

  verifyingComunication = true;             // Marca a verificação como iniciada
    
  ComandoEscravo = ACK_MSG;                 // Define a mensagem de envio para o escravo como ACK_MSG
  mensagemStr = "{\"ACK_MSG\":1}";          // Define a mensagem de envio para o escravo como ACK_MSG
  slaveSendHandler();                       // Chama a função de manipulação de envio para o escravo.


  if (hasComunication) {                    //Erro relacionado as funções wire.endtransmission
    printString("\nConexao com o escravo estabelecida");
  } else {
    printString("\nErro na conexao com o escravo");
  }

  verifyingComunication = false;            // Marca a verificação como iniciada

  return hasComunication;
}


// Função para gerenciar o websocket do servidor
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
    switch(type) {
        case WStype_DISCONNECTED:
            printString("[" + String(num) + "] Disconnected!");
            break;
        case WStype_CONNECTED:
            printString("[" + String(num) + "] Connected from  . . .  url: 192.168.4.1");
            printString(String((char *) payload));
            webSocket.sendTXT(num, "Conectado");

            if (RTKAtual !=-1){
              printString("Envio de RTK");
              webSocket.sendTXT(num, "{\"Mensagem\": \"RTK\", \"Valor\": " + String(RTKAtual) + "}");
            }
            if (precisaoRTK !=-1){
              printString("Envio de precisao");
              webSocket.sendTXT(num, "{\"Mensagem\": \"PRECISAO\", \"Valor\": " + String(precisaoRTK) + "}");
            }
        break;
        case WStype_TEXT:
            printString("[" + String(num) + "] Received: ");
            printString(String((char *) payload));
            break;
    }
}