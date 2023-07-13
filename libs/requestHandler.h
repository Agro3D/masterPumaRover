#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H



// Função para lidar com o envio de dados para o escravo.
void slaveSendHandler() {
  if (ComandoEscravo == 0){ return; }
  
  int x;

  // Caso a mensagem esteja vazia, envie um objeto JSON vazio
  if (mensagemStr == "") { mensagemStr = "{}"; }

    // Mostrar o objeto JSON a ser enviado para o escravo
  mensagemStr = "{\"Comando\":" + String( ComandoEscravo ) +
    ",\"Tamanho\":" + String( mensagemStr.length() ) +
    ",\"Mensagem\":" + mensagemStr + "}";
    

  for (x = 0; x <= SEND_DATA_TRIES; x++) {                    // Tentar enviar os dados para o escravo por um número limitado de vezes
    slaveSendData(mensagemStr);                               // Enviar dados para o slave
    Serial.println("\nDados enviados para o escravo");
    
    String slaveResponse = slaveReceiveResponse();            // Solicite a resposta do escravo
    Serial.println("Resposta do escravo: " + slaveResponse);

    if (slaveResponse == "ACK") {                             // Se a resposta do escravo for "ACK", saia do loop
    mensagemStr = "";                                        // Limpe a mensagem
    hasComunication = true;
      break;
    } else {                                                  // Se a resposta do escravo não for "ACK", continue no loop
      Serial.println("\nErro ao enviar dados para o escravo");

      if (x == SEND_DATA_TRIES) {                             // Se o número máximo de tentativas for atingido, tente reestabelecer a comunicação com o escravo
        Serial.println("Numero maximo de tentativas atingido.");
        Serial.println("Verificando a comunicacao com o escravo...");

        // Tentar reestabelecer a comunicação com o escravo uma vez
        if (!verifyingComunication)
        {
          if (verifyComunication()) {
            Serial.println("Tente novamente em alguns instantes.");
            return;
            }
        }
        
      } else{                                                 // Se o número máximo de tentativas não for atingido, continue no loop
        Serial.println("Tentando novamente...");
      }
    }
  }


  // Ações a serem executadas após o envio dos dados para o escravo
  switch (ComandoEscravo)
  {
  case ACK_MSG:
    hasComunication = true;
    break;
  case GET_STATUS:
    Serial.println("\nRequisição de status enviada para o escravo");
    break;
  case NOVA_CONFIGURACAO:
    Serial.println("\nNova configuração enviada para o escravo");
    break;
  case PARAR_TRABALHO:
    Serial.println("\nRequisição de parada de trabalho enviada para o escravo");
    break;
  
  default:
    Serial.println("\nComando Desconhecido");
    Serial.println("Comando: " + String(ComandoEscravo));
    break;
  }
}


// Função para enviar dados para o escravo.
void slaveSendData(String data) {
  Serial.println("\n\nEnviando dados para o slave");
  Serial.println(mensagemStr);
  
  MySerial.println(data);
  delay(300);
}





#endif // REQUEST_HANDLER_H