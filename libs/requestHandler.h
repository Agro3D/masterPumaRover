#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H


// Este arquivo contém as funções para lidar com as requisições HTTP e envia-las para o escravo



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


    // Verifica se a resposta do escravo é um ACK/NACK ou uma mensagem de comando,
    // caso seja uma mensagem de comando, execute a função de atualização do RTK e da Precisão
    // e continue no loop até receber um ACK/NACK
    while (slaveResponse.indexOf("Comando") != -1 && slaveResponse.indexOf("ACK") == -1 && slaveResponse.indexOf("NACK") == -1){
      DynamicJsonDocument json(128);
      deserializeJson(json, slaveResponse);
      updateRTK(json["Comando"].as<int>(), json["Mensagem"].as<int>());
      
      slaveResponse = slaveReceiveResponse();                 // Le a resposta do escravo
      printString("Resposta do escravo: " + slaveResponse);
    }


    // Verifica se a resposta do escravo é um ACK ou um NACK
    if (slaveResponse.indexOf("ACK") != -1 && slaveResponse.indexOf("NACK") == -1) { // Se a resposta do escravo for "ACK", saia do loop
    mensagemStr = "";                                         // Limpe a mensagem
    escravoTrabalhando = true;
    hasComunication = true;
      break;
    } else {                                                  // Se a resposta do escravo não for "ACK", continue no loop
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
      }
    }
  }


  // Ações a serem executadas após o envio dos dados para o escravo
  switch (comandoEscravo)  {
  case ACK_MSG:
    hasComunication = true;
    break;
    
  case GET_STATUS:
    printString("\nRequisição de status enviada para o escravo");
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
  comandoEscravo = -1;
  printString("");
}


// Função para enviar dados para o escravo.
void slaveSendData(String data) {
  printString("\n\nEnviando dados para o slave");
  printString(mensagemStr);
  
  MySerial.println(data);                                     // Envia os dados para o escravo
  delay(300);
}





#endif // REQUEST_HANDLER_H