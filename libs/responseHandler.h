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

  case GET_PRECISAO:
    updateRTK(resposta["Comando"].as<int>(), resposta["Mensagem"].as<int>());
    break;
    
  case GET_RTKSTATUS:
    updateRTK(resposta["Comando"].as<int>(), resposta["Mensagem"].as<int>());
    break;
    
  case NOVO_TRABALHO:
    receberMensagens = true;
    proximoComando();
    statusAtual = char(TRABALHANDO);
    receberMensagens = true;
    break;

  case PARAR_TRABALHO:
    receberMensagens = false;
    RTKAtual = -1;
    precisaoRTK = -1;
    listaPontos = "";
    proximoComando();
    statusAtual = char(ESPERANDO);
    break;

  case NOVO_PONTO:
    novoPonto(resposta["Mensagem"].as<String>());
    webSocket.broadcastTXT("{\"Mensagem\": \"NOVO_PONTO\", \"Valor\": " + resposta["Mensagem"].as<String>() + "}");
    proximoComando();
    break;

  case LISTAR_PONTOS:
    listarPontos(resposta["Mensagem"].as<String>());
    proximoComando();
    break;


  case LISTAR_ARQUIVOS:
    listaArquivosStr = resposta["Mensagem"].as<String>();
    webSocket.broadcastTXT("{\"Mensagem\": \"LISTAR_ARQUIVOS\", \"Valor\": " + listaArquivosStr + "}");
    proximoComando();
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
  DynamicJsonDocument respostaStatus(62);
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
    RTKAtual = respostaStatus["RTK"].as<int>();
    precisaoRTK = respostaStatus["Precisao"].as<int>();
    break;

  default:
    break;
  }

  printString("Status atualizado para: " + statusStr);
  webSocket.broadcastTXT(statusStr);
}


// Função para processar a resposta do RTK/Precisão e enviar para o cliente
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


// Função para ler a resposta do escravo.
String slaveReceiveResponse() {
  printString("Lendo mensagem do slave");
  String response = "";
  unsigned long startTime = millis();

  // Aguarda a chegada de dados do escravo ou aguarda n segundos sem comunicação
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



// Função para gravar a lista de pontos recebida do escravo
void listarPontos(String resposta) {

  if (resposta == "" || resposta == NULL || resposta.length() < 2) {
    listaPontos = "\"\"";
  } else {
    resposta.replace("\\n", "<br />");
    listaPontos = resposta;
  }
  
  printString("Pontos: " + listaPontos);
  
  webSocket.broadcastTXT("{\"Mensagem\": \"LISTAR_PONTOS\", \"Valor\": " + listaPontos + "}");
}




#endif // RESPONSE_HANDLER_H