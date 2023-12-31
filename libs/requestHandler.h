#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H


// Este arquivo contém as funções para lidar com o envio de dados para o escravo
// Estes dados tem origem como requisições do cliente através do servidor



// Função para lidar com o envio de dados para o escravo.
void slaveSendHandler() {
  
  printString("\nComando para o escravo: " + String(comandoEscravo));
  int x;

  if (mensagemStr == "") { mensagemStr = "{}"; }              // Caso a mensagem esteja vazia, envie um objeto JSON vazio

  // Monta a mensagem a ser enviada para o escravo
  mensagemStr = "{\"Comando\":" + String( comandoEscravo ) +  
    ",\"Tamanho\":" + String( mensagemStr.length() ) +
    ",\"Mensagem\":" + mensagemStr + "}";
    

  for (x = 0; x <= SEND_DATA_TRIES; x++) {                    // Tentar enviar os dados para o escravo por um número limitado de vezes
    slaveSendData(mensagemStr);                               // Enviar dados para o slave
    printString("\nDados enviados para o escravo");
    
    String slaveResponse = slaveReceiveResponse();            // Le a resposta do escravo
    printString("Resposta do escravo: " + slaveResponse);


    // Verifica se a resposta do escravo é um ACK ou um NACK
    if (slaveResponse.indexOf("ACK") != -1 && slaveResponse.indexOf("NACK") == -1) { // Se a resposta do escravo for "ACK", saia do loop
    mensagemStr = "";                                         // Limpe a mensagem
    hasComunication = true;
      break;
    } else if (slaveResponse.indexOf("NACK") != -1){          // Se a resposta do escravo não for "ACK", continue no loop
      printString("\nErro ao enviar dados para o escravo");

      if (x == SEND_DATA_TRIES) {                             // Se o número máximo de tentativas for atingido, tente reestabelecer a comunicação com o escravo
        printString("Numero maximo de tentativas atingido.");
        printString("Verificando a comunicacao com o escravo...");

        // Verifica a comunicação com o escravo
        if (!verifyingComunication) {
          if (verifyComunication()) {
            printString("Tente novamente em alguns instantes.");
            return;
            }
        }
        
      } else{                                                 // Se o número máximo de tentativas não for atingido, continue no loop
        printString("Tentando novamente...");
      }                                                       // Se a mensagem recebida
    } else if (slaveResponse.indexOf("\"Comando\":" + String(ALERT_MESSAGE)) != -1 ||
               slaveResponse.indexOf("\"Comando\":" + String(SINAL_RADIO)) != -1){
      
      DynamicJsonDocument resposta(256);
      deserializeJson(resposta, slaveResponse);                // Le a resposta do escravo e converte para json

      printString("");
      printString("Mensagem de alerta recebida: ");
      printString("Mensagem: " + slaveResponse);
      printString("");

      switch (resposta["Comando"].as<int>())
      {
      case ALERT_MESSAGE:
        webSocket.broadcastTXT(resposta["Mensagem"].as<String>().c_str());
        break;
      case SINAL_RADIO:
        atualizaSinalRadio(resposta["Mensagem"].as<int>());
        break;
      }
    }
  }


  // Ações a serem executadas após o envio dos dados para o escravo
  switch (comandoEscravo)  {
  case ACK_MSG:
    hasComunication = true;
    break;

  case INICIALIZAR:
    printString("\nInicializando o Sistema");
    break;
    
  case GET_STATUS:
    printString("\nRequisição de status enviada para o escravo");
    break;
    
  case GET_CARTAOSD:
    printString("\nRequisição de cartão SD enviada para o escravo");
    break;
    
  case HEAP_SIZE:
    printString("\nEnviando tamanho da heap para o escravo");
    break;

  case NOVO_TRABALHO:
    printString("\nNova configuração enviada para o escravo");
    break;

  case PARAR_TRABALHO:
    printString("\nRequisição de parada de trabalho enviada para o escravo");
    break;

  case NOVO_PONTO:
    printString("\nRequisição de novo ponto enviada para o escravo");
    break;

  case LISTAR_ARQUIVOS:
    printString("\nRequisição de listagem de arquivos enviada para o escravo");
    break;
  
  case LISTAR_PONTOS:
    printString("\nRequisição de listagem de pontos enviada para o escravo");
    break;
  
  default:
    printString("\nComando Desconhecido");
    printString("Comando: " + String(comandoEscravo));
    break;
  }

  lastComandSend = millis();

  if(comandoEscravo == HEAP_SIZE){
    proximoComando();
  }else {
    comandoEscravo = -1;
    printString("");
  }
}


// Função para enviar dados para o escravo.
void slaveSendData(String data) {
  printString("\n\nEnviando dados para o slave");
  printString(mensagemStr);
  
  MySerial.println(data);                                     // Envia os dados para o escravo
  delay(300);
}





#endif // REQUEST_HANDLER_H