#ifndef ZEDHANDLER_H
#define ZEDHANDLER_H


// Este arquivo contém as funções para lidar com o ZED-F9P 


// Função para receber e processar a mensagem do ZED-F9P
void processaMensagem(String message){

  // Verifica qual o tipo de mensagem recebida
  if(message.indexOf("$GNGGA") != -1){
    // Processa a mensagem recebida retornando a cota elipsoidal
    processaNMEAGGA(message);

  }else if(message.indexOf("PUBX") != -1){
    // Processa a mensagem recebida retornando a precisao vertical e horizontal
    processaNMEAPUBX(message);
  }
}



// Função para pegar a cota do GPS, calculando a cota elipsoidal
void processaNMEAGGA(String nmeastr) {

  int lastCommaIndex = 0;
  int currentCommaIndex = 0;
  int commaCount = 0;
  String piece;

  // Percorre a mensagem atraves das vírgulas
  while (currentCommaIndex != -1) {
    currentCommaIndex = nmeastr.indexOf(',', lastCommaIndex);

    // Pega o elemento da mensagem entre as vírgulas
    if (currentCommaIndex != -1) {
      piece = nmeastr.substring(lastCommaIndex, currentCommaIndex);
      lastCommaIndex = currentCommaIndex + 1;
    } else {
      piece = nmeastr.substring(lastCommaIndex);
    }

    commaCount++;

    // Verifica qual o elemento da mensagem
    switch (commaCount){

      // Status RTK é o sétimo elemento da mensagem
      case 7:
        if(piece[0] != RTKAtual){
          RTKAtual = piece[0];
          webSocket.broadcastTXT("{\"Mensagem\": \"RTK\", \"Valor\": " + String(RTKAtual) + "}");
        }
        break;

      // Altitude é o décimo elemento da mensagem, altitute nivel do mar
      case 10:
        cota = String(piece);
        break;

      // Verifica se a mensagem é válida
      case 11:
        if (piece[0] != 'M'){ cota = "-1"; }                  // Retorna uma altitude inválida se a mensagem não for válida
        break;
          
      // Diferença elipsoidal é o décimo segundo elemento da mensagem
      case 12:
        cota = String(cota.toFloat() + String(piece).toFloat(), 3);
        break;
        
      default:
        break;
    }
  }

  // Envia a cota para o cliente
  printString("");
  printStringNoBreak("Cota: " + String(cota));

  if (cota.toFloat() >= cotaRefInferior && cota.toFloat() <= cotaRefSuperior){
    printString(" dentro da faixa de referência");
    webSocket.broadcastTXT("{\"Mensagem\": \"Cota\", \"Valor\": " + cota + ", \"Status\": \"CERTO\"}");
  } else{
    printString(" fora da faixa de referência");
    webSocket.broadcastTXT("{\"Mensagem\": \"Cota\", \"Valor\": " + cota + ", \"Status\": \"ERRADO\"}");
  }

  printString("Status code: " + String(RTKAtual));
}


// Função para pegar a cota do GPS, calculando a cota elipsoidal
void processaNMEAPUBX(String pubxstr) {

  // Percorre a mensagem atraves das vírgulas
  String piece;
  int lastCommaIndex = 0;
  int currentCommaIndex = 0;
  int commaCount = 0;
  bool send = false;

  // Percorre a mensagem atraves das vírgulas
  while (currentCommaIndex != -1) {
    currentCommaIndex = pubxstr.indexOf(',', lastCommaIndex);

    // Pega o elemento da mensagem entre as vírgulas
    if (currentCommaIndex != -1) {
      piece = pubxstr.substring(lastCommaIndex, currentCommaIndex);
      lastCommaIndex = currentCommaIndex + 1;
    } else {
      piece = pubxstr.substring(lastCommaIndex);
    }

    commaCount++;

    // Verifica qual o elemento da mensagem
    switch (commaCount){

      // Precisao horizontal é o décimo elemento da mensagem
      case 10:
        if (piece != precisaoHorizontal){
          precisaoHorizontal = String(piece);
          send = true;
        }
        break;

      // Precisao vertical é o décimo primeiro elemento da mensagem
      case 11:
        if (piece != precisaoVertical){
          precisaoVertical = String(piece);
          send = true;
        }
        break;
        
      default:
        break;
    }
  }

  if (send){
    printString("");
    printString("Precisão horizontal: " + precisaoHorizontal);
    printString("Precisão vertical: " + precisaoVertical);

    // Envia a precisao para o cliente
    webSocket.broadcastTXT("{\"Mensagem\": \"PRECISAO\", \"Valor\": {\"precisaoVertical\": " +
                            precisaoVertical + ", \"precisaoHorizontal\": " + precisaoHorizontal + "}}");
  }
}






#endif // ZEDHANDLER_H