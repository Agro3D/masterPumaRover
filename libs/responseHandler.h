#ifndef RESPONSE_HANDLER_H
#define RESPONSE_HANDLER_H


// Este arquivo contém as funções para lidar com as respostas do escravo


// Função para processar a resposta do escravo e configurar o proximo comando a ser enviado
void slaveReceiveHandler() {
  
  DynamicJsonDocument resposta(10240);
  deserializeJson(resposta, slaveReceiveResponse());          // Le a resposta do escravo e converte para json

  printString("Mensagem do escravo: ");
  printJson(resposta);
  printString("");
  printString("");


  switch (resposta["Comando"].as<int>()){
  case GET_STATUS:
    getStatus(resposta["Mensagem"].as<String>());
    proximoComando();
    break;
    
  case NOVO_TRABALHO:
    receberMensagens = true;
    proximoComando();
    statusAtual = char(TRABALHANDO);

    
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

  case PARAR_TRABALHO:
    receberMensagens = false;
    RTKAtual = '-1';
    precisaoHorizontal = -1;
    precisaoVertical = -1;
    alturaBastao = 0;
    cotaRef = FLT_MIN;
    cotaRefInferior = FLT_MIN;
    cotaRefSuperior = FLT_MIN;
    deserializeJson(listaPontos, "{\"Pontos\": []}");

    proximoComando();
    statusAtual = char(ESPERANDO);
    break;

  case NOVO_PONTO:
    novoPonto(resposta["Mensagem"]);
    webSocket.broadcastTXT("{\"Mensagem\": \"NOVO_PONTO\", \"Valor\": " + resposta["Mensagem"].as<String>() + "}");
    proximoComando();
    break;

  case RESP_LISTAR_PONTOS:
    listarPontos(resposta["Mensagem"].as<String>());
    break;

  case LISTAR_PONTOS:
    listarPontos(resposta["Mensagem"].as<String>());    
    webSocket.broadcastTXT("{\"Mensagem\": \"LISTAR_PONTOS\", \"Valor\": " + listaPontos.as<String>() + "}");
    proximoComando();
    break;


  case LISTAR_ARQUIVOS:
    listaArquivosStr = resposta["Mensagem"].as<String>();
    webSocket.broadcastTXT("{\"Mensagem\": \"LISTAR_ARQUIVOS\", \"Valor\": " + listaArquivosStr + "}");
    proximoComando();
    break;

  case SINAL_RADIO:
    atualizaSinalRadio(resposta["Mensagem"].as<int>());
    break;

  case ALERT_MESSAGE:
    webSocket.broadcastTXT(resposta["Mensagem"].as<String>().c_str());
    break;

  case HEAP_SIZE:
    proximoComando();
    break;

  default:
    break;
  }
}


// Função para processar a reposta de status do escravo
void getStatus(String mensagem){
  
  DynamicJsonDocument respostaStatus(64);
  deserializeJson(respostaStatus, mensagem);

  String statusStr;

  // Configura o status atual do sistema
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
    alturaBastao = respostaStatus["AlturaBastao"].as<float>();
    printString("Altura do bastao: " + String(alturaBastao) + " m");
    break;

  default:
    break;
  }

  printString("Status atualizado para: " + statusStr);
  webSocket.broadcastTXT(statusStr);
}



// Função para ler a resposta do escravo.
String slaveReceiveResponse() {
  
  printString("Lendo mensagem do slave");
  String response = "";
  unsigned long startTime = millis();

  // Aguarda a chegada de dados do escravo ou aguarda n segundos sem comunicação
  while (!MySerial.available() && millis() - startTime < 10000) {}
  
  startTime = millis();

  // Lê os dados do escravo ou aguarda n segundos sem resposta
  while (millis() - startTime < 800) { 
    while (MySerial.available() && millis() - startTime < 5000) { 
      response += (char)MySerial.read();
      startTime = millis();
    }
    response.trim();                    // Remover espaços em branco do início e do final da string
    delay(100);
  }

  return response;
}



// Função para gravar a lista de pontos recebida do escravo
void listarPontos(String resposta) {

  if (resposta == "" || resposta == NULL || resposta.length() < 2) {
    deserializeJson(listaPontos, "[]");
  } else {
    resposta.replace("\\n", "<br />");
    DynamicJsonDocument Pontos(4096);
    deserializeJson(Pontos, resposta);

    for (int i = 0; i < Pontos["Pontos"].size(); i++) {
      listaPontos["Pontos"].add(Pontos["Pontos"][i]);
    }
  }  
}




#endif // RESPONSE_HANDLER_H