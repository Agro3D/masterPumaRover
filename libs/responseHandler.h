#ifndef RESPONSE_HANDLER_H
#define RESPONSE_HANDLER_H



void slaveReceiveHandler() {

  switch (ComandoEscravo)
  {
  case LISTA_ARQUIVOS:
    listaArquivos();
    ComandoEscravo = 0;
    webSocket.broadcastTXT("refreshStatus");
    break;

  case GET_STATUS:
    getStatus();
    ComandoEscravo = 0;
    break;

  case NOVO_TRABALHO:
    webSocket.broadcastTXT("refreshStatus");
    ComandoEscravo = 0;
    break;

  case CANCELAR_TRABALHO:
    webSocket.broadcastTXT("refreshStatus");
    ComandoEscravo = 0;
    break;

  case FINALIZAR_TRABALHO:
    ComandoEscravo = LISTA_ARQUIVOS;
    break;

  case CANCELAR_PESQUISA:
    webSocket.broadcastTXT("refreshStatus");
    ComandoEscravo = 0;
    break;

  case EXCLUIR_ARQUIVOS:
    excluirArquivos();
    ComandoEscravo = LISTA_ARQUIVOS;
    break;
  
  default:
    slaveListerner();
    ComandoEscravo = 0;
    break;
  }
}


void getStatus() {
  DynamicJsonDocument respostaStatus(1024);
  deserializeJson(respostaStatus, slaveReceiveResponse());
  // String status = slaveReceiveResponse();
  int status =  respostaStatus["Mensagem"].as<int>();
  String statusStr;

  switch (status)
  {
  case ESPERANDO:
    statusStr = "Esperando";
    break;
  case PESQUISANDO:
    statusStr = "Pesquisando";
    break;
  case PROCESSANDO:
    statusStr = "Processando";
    break;
  case SALVANDO:
    statusStr = "Salvando";
    break;

  default:
    break;
  }

  Serial.println("Status do escravo: " + statusStr);
  webSocket.broadcastTXT(statusStr);
}


void slaveListerner() {
  DynamicJsonDocument resposta(1024);
  deserializeJson(resposta, slaveReceiveResponse());
  
  Serial.println("Escravo: ");
  serializeJsonPretty(resposta, Serial);
  Serial.println();

  if (resposta["Mensagem"] == "PesquisaFinalizada"){
    webSocket.broadcastTXT("Processando");
  } 
}


// Função para receber a resposta do escravo.
String slaveReceiveResponse() {
  Serial.println("Esperando resposta do slave");
  String response = "";
  unsigned long startTime = millis();

  while (!MySerial.available() && millis() - startTime < 10000) {}
  
  startTime = millis();

  // Lê os dados do escravo ou aguarda n segundos sem resposta
  while (millis() - startTime < 1000) { 
    while (MySerial.available() && millis() - startTime < 5000) { 
      response += (char)MySerial.read();
      startTime = millis();
    }
    response.trim();                    // Remover espaços em branco do início e do final da string
    delay(100);
  }

  
  return response;
}


void listaArquivos() {
  DynamicJsonDocument resposta(10240);
  String slaveResponse = slaveReceiveResponse();            // Solicite a resposta do escravo

  Serial.println(slaveResponse);
  
  deserializeJson(resposta, slaveResponse);
  listaArquivosStr = resposta["Mensagem"].as<String>();     // Armazene a lista de arquivos do escravo

  Serial.println("Resposta do escravo:");
  serializeJsonPretty(resposta, Serial);
  Serial.println();
}


void excluirArquivos() {
  String slaveResponse = slaveReceiveResponse();            // Solicite a resposta do escravo
  Serial.println(slaveResponse);
}

#endif // RESPONSE_HANDLER_H