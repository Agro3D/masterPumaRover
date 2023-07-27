#ifndef RESPONSE_HANDLER_H
#define RESPONSE_HANDLER_H


// Função para passo a passo da comunicação com o escravo
void slaveReceiveHandler() {

  switch (ComandoEscravo){
  case GET_STATUS:
    getStatus();
    ComandoEscravo = 0;
    break;
  case NOVO_TRABALHO:
    receberMensagens = true;
    ComandoEscravo = GET_STATUS;
    statusAtual = char(TRABALHANDO);
    break;

  case PARAR_TRABALHO:
    receberMensagens = false;
    RTKAtual = -1;
    precisaoRTK = -1;
    ComandoEscravo = GET_STATUS;
    statusAtual = char(ESPERANDO);
    break;

  case NOVO_PONTO:
    ComandoEscravo = 0;
    break;

  case LISTAR_ARQUIVOS:
    listaArquivos();
    ComandoEscravo = GET_STATUS;
    break;

  
  default:
    slaveListerner();
    break;
  }
}



void getStatus() {
  DynamicJsonDocument respostaStatus(256);
  deserializeJson(respostaStatus, slaveReceiveResponse());
  // String status = slaveReceiveResponse();
  int status =  respostaStatus["Mensagem"].as<int>();
  String statusStr;

  switch (status){
  case ESPERANDO:
    statusStr = "Esperando";
    statusAtual = char(ESPERANDO);
    break;
  case TRABALHANDO:
    statusStr = "TRABALHANDO";
    statusAtual = char(TRABALHANDO);
    break;

  default:
    break;
  }

  Serial.println("Status do escravo: " + statusStr);
  webSocket.broadcastTXT(statusStr);
}



// Função para receber a resposta do escravo.
void slaveListerner() {
  DynamicJsonDocument resposta(128);
  deserializeJson(resposta, slaveReceiveResponse());            // Le a resposta do escravo e converte para json
  
  Serial.println("Escravo: ");
  serializeJsonPretty(resposta, Serial);
  Serial.println();

  // Verifica se a resposta é um status 
  updateRTK(resposta);

  switch (resposta["Comando"].as<int>()) {
    case NOVO_PONTO:
    webSocket.broadcastTXT(resposta["Mensagem"].as<String>().c_str());
      break;
  
  default:
    break;
  }

}

void updateRTK(DynamicJsonDocument resposta){

  // Verifica se a resposta é um status ou uma mensagem de precisão e atualiza as variáveis
  if (resposta["Mensagem"] == "Precisao" || resposta["Mensagem"] == "RTK"){
    if(resposta["Mensagem"] == "Precisao"){
      precisaoRTK = resposta["Valor"];
    } else if (resposta["Mensagem"] == "RTK"){
      RTKAtual = resposta["Valor"];
    }

    webSocket.broadcastTXT(resposta.as<String>().c_str());
  } 
}


// Função para receber a resposta do escravo.
String slaveReceiveResponse() {
  Serial.println("Esperando mensagem do slave");
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



#endif // RESPONSE_HANDLER_H