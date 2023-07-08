// Variáveis Globais
#include "libs/common.h"              // Variáveis globais


// Função para realizar a configuração inicial do servidor web.
void setup() {
  Serial.begin(115200);
  MySerialZed.begin(19200, SERIAL_8N1, RX, TX);     // Set up the hardware serial port
  delay(2000);
  
  // Imprime linhas de separação e mensagens de inicialização no console serial.
  Serial.println();
  Serial.println();
  Serial.println("============================================================");
  Serial.println("  ----- Inicializando o Master Puma Rover RTK -----  ");
  // Serial.println("Versao do Arduino: " + String(ARDUINO));

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


  // Inicia o protocolo I2C como master.
  Serial.println();
  Serial.println("Iniciando Comunicação UART");
  MySerial.begin(480600, SERIAL_8N1, MYPORT_RX, MYPORT_TX);     // Set up the hardware serial port
  delay(1000);
  while (MySerial.available()) MySerial.read();

  Serial.println("Comunicação UART Inicializado");


  // Inicia o servidor web e imprime uma mensagem no console serial.
  Serial.println();
  Serial.println("Iniciando o servidor HTTP");
  setupServer();
  server.begin();
  Serial.println("Servidor HTTP iniciado em http://" + String(IP.toString()));


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
  // if(ComandoEscravo || MySerial.available()) {
  //   Serial.println("Comando recebido do escravo: " + String(ComandoEscravo));
  //   slaveSendHandler();                           // Chama a função de manipulação de envio para o escravo.
  //   slaveReceiveHandler();                        // Chama a função de manipulação de recebimento do escravo.
  // }


  Serial.println("Verificando mensagens na UART0...");
  while (MySerialZed.available()) {
    String message = MySerialZed.readStringUntil('\n');
    
    String cota = getAltitudeFromNMEA(message);
    if(cota != "-1.00"){
      Serial.println("Cota: " + String(cota));
      webSocket.broadcastTXT(cota);
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
        case WStype_CONNECTED: {
            Serial.printf("[%u] Connected from  . . .  url: 192.168.4.1%s\n", num, payload);
            // webSocket.sendTXT(num, "Conectado");
        }
        break;
        case WStype_TEXT:
            Serial.printf("[%u] Received: %s\n", num, payload);
            break;
    }
}