// Impoção de bibliotecas, váriaveis globais, módulos e funções
#include "libs/common.h"


// Este programa é responsável por controlar o Master Puma Rover RTK.



// Função para realizar a configuração inicial do mestre.
void setup() {
  delay(6000);
  Serial.begin(115200);
  
  // Imprime linhas de separação e mensagens de inicialização no console serial.
  printString("");
  printString("");
  printString("============================================================");
  printString("  ----- Inicializando o Master Puma Rover RTK -----  ");


  printString("");
  printString("Iniciando Comunicação UART (Escravo)");
  MySerial.begin(460800, SERIAL_8N1, MYPORT_RX, MYPORT_TX);       // Inicia o protocolo UART para comunicação com o escravo.
  delay(1000);
  while (MySerial.available()) MySerial.read();                   // Limpa o buffer de recebimento da UART.

  printString("Comunicação UART (Escravo) Inicializada");



  printString("");
  printString("Iniciando Comunicação UART (ZED)");
  MySerialZed.begin(460800, SERIAL_8N1, RX, TX);                  // Inicia o protocolo UART para comunicação com o ZED.
  delay(1000);
  while (MySerialZed.available()) MySerialZed.read();             // Limpa o buffer de recebimento da UART.

  printString("Comunicação UART (ZED) Inicializada");



  printString("");
  printString("Inicializando o WiFi");
  while(!WiFi.softAP(ssid, password)) {                           // Inicia o WiFi no modo AP com o SSID e a senha definidos.
    printString("Falha na configuracao do AP");
    printString("Tentando novamente...");
    delay(1000);
  }



  printString("WiFi Inicializado");                               // Imprime informações sobre o AP no console serial.
  printString("SSID: .................................. " + String(ssid));
  printString("Senha: ................................. " + String(password));
  printString("MAC Address: ........................... " + WiFi.softAPmacAddress());

  IPAddress IP = WiFi.softAPIP();
  printStringNoBreak("Endereco de IP do Access Point: ........ ");
  printString(String(IP));



  printString("Inicializando o servidor WebSocket");
  webSocket.begin();                                              // Iniciar o servidor WebSocket
  webSocket.onEvent(webSocketEvent);                              // Configura a função de manipulação de eventos do servidor WebSocket.
  printString("Servidor WebSocket Inicializado");


  printString("");
  printString("Iniciando o servidor HTTP");
  setupServer();                                                  // Configura o servidor HTTP.
  server.begin();                                                 // Inicia o servidor web
  printString("Servidor HTTP iniciado em http://" + String(IP.toString()));


  comandoEscravo = INICIALIZAR;                                   // Envia o comando de lista de arquivos para o escravo.
  slaveSendHandler();                                             // Chama a função de manipulação de envio para o escravo.
  slaveReceiveHandler();                                          // Chama a função de manipulação de recebimento do escravo.


  statusAtual = char(ESPERANDO);
  listaPontos = "";


  printString("\n\n\tMaster Puma Rover inicializado.");

  printString("");
  printString("============================================================");
  printString("");
  printString("Servidor aguardando requisicoes...");
  printString("");
}


// Função principal executada repetidamente após a função de inicialização.
void loop() {

  // Verifica se ha alguma requisicao do cliente, caso haja, processa e envia a requisicao para o escravo.
  if(comandoEscravo != -1) { slaveSendHandler(); }

  // Verifica se ha alguma mensagem do escravo, caso haja, processa a mensagem recebida.
  if(MySerial.available()) { slaveReceiveHandler(); }



  // Lê as mensagens recebidas do ZED
  while (MySerialZed.available()) {
    String message = MySerialZed.readStringUntil('\n');

    // Caso esteja trabalhando, processa a mensagem recebida.
    if(receberMensagens){
      processaMensagem(message);
    }
  }



  // Verifica o uso de memória do ESP32 e imprime um aviso caso o uso de memória tenha aumentado.
  static uint32_t lastHeapSize = 0;
  uint32_t currentHeapSize = ESP.getFreeHeap();

  // Caso o tamanho da memória tenha diminuido desde a última iteração do loop, imprime um aviso.
  if (currentHeapSize < lastHeapSize) {
    printStringNoBreak("WARNING: Heap size decreased! Current heap size: ");
    printString(String(currentHeapSize));
  }

  // Atualiza o tamanho da memória da última iteração do loop.
  lastHeapSize = currentHeapSize;

  if(millis() - lastHeapSend > HEAP_SIZE_TIMER){
    lastHeapSend = millis();
    comandoEscravo = HEAP_SIZE;
    mensagemStr = String(currentHeapSize);
  }


  // Realiza o loop do servidor WebSocket.
  webSocket.loop();
  delay(200);
}


// Função para verificar se a comunicação com o escravo foi estabelecida
bool verifyComunication(){
  printStringNoBreak("Verificando a conexao com o escravo...");

  verifyingComunication = true;             // Marca a verificação como iniciada
    
  comandoEscravo = ACK_MSG;                 // Define o comando para o escravo como ACK_MSG
  mensagemStr = "{\"ACK_MSG\":1}";          // Define a mensagem de envio para o escravo como ACK_MSG
  slaveSendHandler();                       // Chama a função de manipulação de envio para o escravo.


  if (hasComunication) {                    //Erro relacionado as funções wire.endtransmission
    printString("\nConexao com o escravo estabelecida");
  } else {
    printString("\nErro na conexao com o escravo");
  }

  verifyingComunication = false;            // Marca a verificação como finalizada

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

            // Caso o RTK esteja definido, envia o valor para o cliente.
            if (RTKAtual !=-1){
              printString("Envio de RTK");
              webSocket.sendTXT(num, "{\"Mensagem\": \"RTK\", \"Valor\": " + String(RTKAtual) + "}");
            }

            // Caso a precisão esteja definida, envia o valor para o cliente.
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