#ifndef RESPONSE_HANDLER_H
#define RESPONSE_HANDLER_H


// Função para passo a passo da comunicação com o escravo
void slaveReceiveHandler() {
  DynamicJsonDocument resposta(10240);
  deserializeJson(resposta, slaveReceiveResponse());                 // Le a resposta do escravo e converte para json

  Serial.println("Mensagem do escravo: ");
  serializeJsonPretty(resposta, Serial);
  Serial.println();
  Serial.println();

  // Serial.println("Tamanho da resposta: " + String(resposta["Tamanho"].as<int>()));


  switch (resposta["Comando"].as<int>()){
  case GET_STATUS:
    getStatus(resposta["Mensagem"].as<String>());

    Serial.println("Proximo: " + String(proximoComandoEscravo));
    Serial.println("ProximaMsg: " + mensagemStrAux);
    if(proximoComandoEscravo){
      ComandoEscravo = proximoComandoEscravo;
      mensagemStr = mensagemStrAux;
      
      proximoComandoEscravo = 0;
      mensagemStrAux = "";

    } else {
      escravoTrabalhando = false;
      ComandoEscravo = 0;
    }
    break;

  case GET_PRECISAO:
    updateRTK(resposta["Comando"].as<int>(), resposta["Mensagem"].as<int>());
    break;
    
  case GET_RTKSTATUS:
    updateRTK(resposta["Comando"].as<int>(), resposta["Mensagem"].as<int>());
    break;
    
  case NOVO_TRABALHO:
    receberMensagens = true;
    ComandoEscravo = LISTAR_PONTOS;
    statusAtual = char(TRABALHANDO);
    break;

  case PARAR_TRABALHO:
    receberMensagens = false;
    RTKAtual = -1;
    precisaoRTK = -1;
    ComandoEscravo = LISTAR_ARQUIVOS;
    statusAtual = char(ESPERANDO);
    break;

  case NOVO_PONTO:
    webSocket.broadcastTXT("{\"Mensagem\": \"NOVO_PONTO\", \"Valor\": \"" + resposta["Mensagem"].as<String>() + "\"}");
    ComandoEscravo = 0;
    escravoTrabalhando = false;
    break;

  case LISTAR_PONTOS:
    listarPontos(resposta["Mensagem"].as<String>());
    ComandoEscravo = GET_STATUS;
    break;


  case LISTAR_ARQUIVOS:
    listaArquivosStr = resposta["Mensagem"].as<String>();
    ComandoEscravo = GET_STATUS;
    break;

  case ALERT_MESSAGE:
    webSocket.broadcastTXT(resposta["Mensagem"].as<String>().c_str());
    break;

  default:
    break;
  }
}


void getStatus(String mensagem){
  DynamicJsonDocument respostaStatus(62);
  deserializeJson(respostaStatus, mensagem);

  String statusStr;


  switch (respostaStatus["Status"].as<int>()){
  case ESPERANDO:
    statusStr = "ESPERANDO";
    statusAtual = char(ESPERANDO);
    receberMensagens = false;
    break;
  case TRABALHANDO:
    statusStr = "TRABALHANDO";
    statusAtual = char(TRABALHANDO);
    receberMensagens = true;
    RTKAtual = respostaStatus["RTK"].as<int>();
    precisaoRTK = respostaStatus["Precisao"].as<int>();
    break;

  default:
    break;
  }

  Serial.println("Status atualizado para: " + statusStr);
  webSocket.broadcastTXT(statusStr);
}


void updateRTK(int comando, int valor) {

  String mensagem;

  switch (comando){
  case GET_PRECISAO:
    mensagem = "{\"Mensagem\": \"PRECISAO\", \"Valor\": \"" + String(valor) + "\"}";
    precisaoRTK = valor;
    break;
    
  case GET_RTKSTATUS:
    mensagem = "{\"Mensagem\": \"RTK\", \"Valor\": \"" + String(valor) + "\"}";
    RTKAtual = valor;
    break;
  
  default:
    break;
  }

  webSocket.broadcastTXT(mensagem); 
}

// Função para receber a resposta do escravo.
String slaveReceiveResponse() {
  Serial.println("Lendo mensagem do slave");
  String response = "";
  unsigned long startTime = millis();

  // Aguarda a chegada de dados do escravo ou aguarda n segundos sem resposta
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


void listarPontos(String resposta) {

  listaPontos = resposta;

  Serial.println("Pontos: " + listaPontos);
  
  webSocket.broadcastTXT("{\"Mensagem\": \"LISTAR_PONTOS\", \"Valor\": " + listaPontos + "}");
}



#endif // RESPONSE_HANDLER_H