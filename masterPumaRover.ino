// Impoção de bibliotecas, váriaveis globais, módulos e funções
#include "libs/common.h"


// Este programa é responsável por controlar o Master Puma Rover RTK.



// Função para realizar a configuração inicial do mestre.
void setup() {

  // Inicialização dos pinos Utilizados no sistema
  pinMode(POWER_CHECK, INPUT);
  pinMode(POWER_OFF, OUTPUT);
  pinMode(LED_STATUSRTK, OUTPUT);

  digitalWrite(POWER_OFF, HIGH);

  // Delay inicial para prevenir bugs na inicialização.
  delay(6000);
  Serial.begin(115200);
  
  // Imprime linhas de separação e mensagens de inicialização no console serial.
  printString("");
  printString("");
  printString("============================================================");
  printString("  ----- Inicializando o Master Puma Rover RTK -----  ");


  printString("");
  printString("Iniciando Comunicação UART (Escravo)");
  MySerial.begin(ESP_COMM_SPEED, SERIAL_8N1, MYPORT_RX, MYPORT_TX);       // Inicia o protocolo UART para comunicação com o escravo.
  delay(1000);
  MySerial.flush();                                                       // Limpa o buffer de envio da UART.
  while (MySerial.available()) MySerial.read();                           // Limpa o buffer de recebimento da UART.

  printString("Comunicação UART (Escravo) Inicializada");



  printString("");
  printString("Iniciando Comunicação UART (ZED)");
  MySerialZed.begin(ZED_COMM_SPEED, SERIAL_8N1, RX, TX);          // Inicia o protocolo UART para comunicação com o ZED.
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
  printString("Endereco de IP do Access Point: ........ " + IP.toString());
  printString("Endereco de IP do gateway: ............. " + WiFi.gatewayIP().toString());
  printString("Endereco de IP da mascara de subrede: .. " + WiFi.subnetMask().toString());



  printString("");
  printString("Inicializando o servidor WebSocket");
  webSocket.begin();                                              // Iniciar o servidor WebSocket
  webSocket.onEvent(webSocketEvent);                              // Configura a função de manipulação de eventos do servidor WebSocket.
  printString("Servidor WebSocket Inicializado");


  printString("");
  printString("Iniciando o servidor HTTP");
  setupServer();                                                  // Configura o servidor HTTP.
  server.begin();                                                 // Inicia o servidor web
  printString("Servidor HTTP iniciado em http://" + String(IP.toString()));


  comandoEscravo = GET_STATUS;                                    // Envia o comando de lista de arquivos para o escravo.
  slaveSendHandler();                                             // Chama a função de manipulação de envio para o escravo.
  slaveReceiveHandler();                                          // Chama a função de manipulação de recebimento do escravo.


  comandoEscravo = INICIALIZAR;                                   // Envia o comando de lista de arquivos para o escravo.
  slaveSendHandler();                                             // Chama a função de manipulação de envio para o escravo.
  slaveReceiveHandler();                                          // Chama a função de manipulação de recebimento do escravo.

  deserializeJson(listaPontos, "{\"Pontos\":[]}");                // Inicializa a lista de pontos de interesse como um array vazio.

  if(statusAtual == char(ESPERANDO)){comandoEscravo = LISTAR_ARQUIVOS;} // Caso o escravo esteja em modo de espera, envia o comando de lista de arquivos para o escravo.
  else{comandoEscravo = LISTAR_PONTOS;}                           // Caso o escravo esteja em modo de trabalho, envia o comando de lista de pontos para o escravo.
  slaveSendHandler();                                             // Chama a função de manipulação de envio para o escravo.
  slaveReceiveHandler();                                          // Chama a função de manipulação de recebimento do escravo.


  printString("");
  printString("Configurando o dual core");

  // Configura o core 0(APP_CORE) para executar a função CommCoreLoop 
  xTaskCreatePinnedToCore(CommCoreLoop,                           // Configura a função para ser executada
                        "TaskComm",                               // Apelida a função com um nuome
                        STACK_SIZE_CPU,                           // Define o tamanho da pilha da função
                        NULL,                                     // Define um parametro para a função, usado para lidar com varios contextos
                        10,                                       // Define a prioridade da função (0-25)
                        &taskCommHandler,                         // Salva o local da função
                        APP_CPU_NUM);                             // Define o core que executará a função

  // Configura o core 1(PRO_CORE) para executar a função ProcessCoreLoop
  xTaskCreatePinnedToCore(ProcessCoreLoop,                        // Configura a função para ser executada
                        "TaskProcess",                            // Apelida a função com um nuome
                        STACK_SIZE_CPU,                           // Define o tamanho da pilha da função
                        NULL,                                     // Define um parametro para a função, usado para lidar com varios contextos
                        10,                                       // Define a prioridade da função (0-25)
                        &taskProcessHandler,                      // Salva o local da função
                        PRO_CPU_NUM);                             // Define o core que executará a função

  printString("Dual core configurado");



  printString("\n\n\tMaster Puma Rover inicializado.");

  printString("");
  printString("============================================================");
  printString("");
  printString("Servidor aguardando requisicoes...");
  printString("");
}


// Função principal executada repetidamente após a função de inicialização.
void loop() {

  // Realiza o loop do servidor WebSocket.
  webSocket.loop();
  delay(1000);
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
  printFuncCore(__func__);

    switch(type) {
        case WStype_DISCONNECTED:
            printString("[" + String(num) + "] Disconnected!");
            break;

        case WStype_CONNECTED:
            printString("[" + String(num) + "] Connected from  . . .  url: 192.168.4.1");
            printString(String((char *) payload));
            webSocket.sendTXT(num, "Conectado");

            if(precisaoHorizontal != "-1" || precisaoVertical != "-1"){
              // Envia a precisao para o cliente
              webSocket.broadcastTXT("{\"Mensagem\": \"PRECISAO\", \"Valor\": {\"precisaoVertical\": " +
                          precisaoVertical + ", \"precisaoHorizontal\": " + precisaoHorizontal + "}}");
            }

            if(RTKAtual != '-1'){
              // Envia o status do RTK para o cliente
              webSocket.broadcastTXT("{\"Mensagem\": \"RTK\", \"Valor\": " + String(RTKAtual) + "}");
            }
        break;

        case WStype_TEXT:
            printString("[" + String(num) + "] Received: ");
            printString(String((char *) payload));
            break;
    }
}