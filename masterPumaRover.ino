// Variáveis Globais
#include "libs/common.h"                // Variáveis globais


// Função para realizar a configuração inicial do servidor web.
void setup() {
  delay(6000);
  Serial.begin(115200);
  
  // Imprime linhas de separação e mensagens de inicialização no console serial.
  Serial.println();
  Serial.println();
  Serial.println("============================================================");
  Serial.println("  ----- Inicializando o Master Puma Rover RTK -----  ");
  // Serial.println("Versao do Arduino: " + String(ARDUINO));


  // Inicia o protocolo UART para comunicação com o escravo.
  Serial.println();
  Serial.println("Iniciando Comunicação UART (Escravo)");
  MySerial.begin(460800, SERIAL_8N1, MYPORT_RX, MYPORT_TX);     // Set up the hardware serial port
  delay(1000);
  while (MySerial.available()) MySerial.read();

  Serial.println("Comunicação UART (Escravo) Inicializada");



  // Inicia o protocolo UART para comunicação com o ZED.
  Serial.println();
  Serial.println("Iniciando Comunicação UART (ZED)");
  MySerialZed.begin(460800, SERIAL_8N1, RX, TX);                // Set up the hardware serial port
  delay(1000);
  while (MySerialZed.available()) MySerialZed.read();

  Serial.println("Comunicação UART (ZED) Inicializada");


  // Inicia o WiFi no modo AP com o SSID e a senha definidos.
  Serial.println();
  Serial.println("Inicializando o WiFi");
  while(!WiFi.softAP(ssid, password)) {
    Serial.println("Falha na configuracao do AP");
    Serial.println("Tentando novamente...");
    delay(1000);
  }


  // Imprime informações sobre o AP no console serial.
  Serial.println("WiFi Inicializado");
  Serial.println("SSID: .................................. " + String(ssid));
  Serial.println("Senha: ................................. " + String(password));
  Serial.println("MAC Address: ........................... " + WiFi.softAPmacAddress());

  IPAddress IP = WiFi.softAPIP();
  Serial.print("Endereco de IP do Access Point: ........ ");
  Serial.println(IP);


  // Iniciar o servidor WebSocket
  Serial.println("Inicializando o servidor WebSocket");
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  Serial.println("Servidor WebSocket Inicializado");


  // Inicia o servidor web e imprime uma mensagem no console serial.
  Serial.println();
  Serial.println("Iniciando o servidor HTTP");
  setupServer();
  server.begin();
  Serial.println("Servidor HTTP iniciado em http://" + String(IP.toString()));

  statusAtual = char(ESPERANDO);

  Serial.println("\n\n\tMaster Puma Rover inicializado.");

  Serial.println();
  Serial.println("============================================================");
  Serial.println();
  Serial.println("Servidor aguardando requisicoes...");
  Serial.println();
}


// Função principal do programa
void loop() {
  // Função principal executada repetidamente após a função de inicialização.

  // Verifica se ha alguma requisicao pendente no servidor web, ou alguma mensagem pendente do escravo.
  if(ComandoEscravo || MySerial.available()) {
    Serial.println("Comando recebido do escravo: " + String(ComandoEscravo));
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

  webSocket.loop();
  delay(300);
}


// Função para verificar se a comunicação com o escravo foi estabelecida
bool verifyComunication(){
  Serial.print("Verificando a conexao com o escravo...");

  verifyingComunication = true;             // Marca a verificação como iniciada
    
  ComandoEscravo = ACK_MSG;                 // Define a mensagem de envio para o escravo como ACK_MSG
  mensagemStr = "{\"ACK_MSG\":1}";          // Define a mensagem de envio para o escravo como ACK_MSG
  slaveSendHandler();                       // Chama a função de manipulação de envio para o escravo.


  if (hasComunication) {                    //Erro relacionado as funções wire.endtransmission
    Serial.println("\nConexao com o escravo estabelecida");
  } else {
    Serial.println("\nErro na conexao com o escravo");
  }

  verifyingComunication = false;            // Marca a verificação como iniciada

  return hasComunication;
}


// Função para gerenciar o websocket do servidor
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Disconnected!\n", num);
            break;
        case WStype_CONNECTED:
            Serial.printf("[%u] Connected from  . . .  url: 192.168.4.1%s\n", num, payload);
            webSocket.sendTXT(num, "Conectado");

            if (RTKAtual !=-1){
              Serial.println("Envio de RTK");
              webSocket.sendTXT(num, "{\"Mensagem\": \"RTK\", \"Valor\": " + String(RTKAtual) + "}");
            }
            if (precisaoRTK !=-1){
              Serial.println("Envio de precisao");
              webSocket.sendTXT(num, "{\"Mensagem\": \"Precisao\", \"Valor\": " + String(precisaoRTK) + "}");
            }
        break;
        case WStype_TEXT:
            Serial.printf("[%u] Received: %s\n", num, payload);
            break;
    }
}