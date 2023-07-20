#ifndef RESPONSE_HANDLER_H
#define RESPONSE_HANDLER_H


// Função para passo a passo da comunicação com o escravo
void slaveReceiveHandler() {

  switch (ComandoEscravo)
  {
  case NOVA_CONFIGURACAO:
    receberMensagens = true;
    ComandoEscravo = 0;
    break;

  case PARAR_TRABALHO:
    receberMensagens = false;
    RTKAtual = -1;
    precisaoRTK = -1;
    ComandoEscravo = 0;
    break;

  case NOVO_PONTO:
    ComandoEscravo = 0;
    break;

  
  default:
    slaveListerner();
    ComandoEscravo = 0;
    break;
  }
}



// Função para receber a resposta do escravo.
void slaveListerner() {
  String mensagemStr = slaveReceiveResponse();
  DynamicJsonDocument resposta(1024);
  deserializeJson(resposta, mensagemStr);
  
  Serial.println("Escravo: ");
  serializeJsonPretty(resposta, Serial);
  Serial.println();

  if (resposta["Mensagem"] == "Precisao" || resposta["Mensagem"] == "RTK"){
    if(resposta["Mensagem"] == "Precisao"){
      precisaoRTK = resposta["Valor"];
    } else if (resposta["Mensagem"] == "RTK"){
      RTKAtual = resposta["Valor"];
    }
    
    webSocket.broadcastTXT(mensagemStr);
  } 
}


// Função para receber a resposta do escravo.
String slaveReceiveResponse() {
  Serial.println("Esperando mensagem do slave");
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



#endif // RESPONSE_HANDLER_H