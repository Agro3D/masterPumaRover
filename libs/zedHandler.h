#ifndef ZEDHANDLER_H
#define ZEDHANDLER_H


// Este arquivo contém as funções para lidar com o ZED-F9P 


// Função para receber e processar a mensagem do ZED-F9P
void processaMensagem(String message){

  // Processa a mensagem recebida retornando a cota elipsoidal
  String cota = getAltitudeFromNMEA(message);


  // Se a cota for válida, envia a cota para o cliente
  if(cota != "-1.00"){

    printString("");
    printStringNoBreak("Cota: " + String(cota));

    if (cota.toFloat() >= cotaRefInferior && cota.toFloat() <= cotaRefSuperior){
      printString(" dentro da faixa de referência");
      webSocket.broadcastTXT("{\"Mensagem\": \"Cota\", \"Valor\": " + cota + ", \"Status\": \"CERTO\"}");
    } else{
      printString(" fora da faixa de referência");
      webSocket.broadcastTXT("{\"Mensagem\": \"Cota\", \"Valor\": " + cota + ", \"Status\": \"ERRADO\"}");
    }
  }
}



// Função para pegar a cota do GPS, calculando a cota elipsoidal
String getAltitudeFromNMEA(String nmeastr) {
  char* nmea = (char*) nmeastr.c_str();

  // Divide a string em substrings separadas por vírgula
  nmea = strtok(nmea, ",");

  // Verifica se a mensagem é do tipo GNGGA
  if (strcmp(nmea, "$GNGGA") != 0) { return "-1.00"; }        // Retorna uma altitude inválida se a mensagem não for do tipo GNGGA


  printString("Mensagem GNGGA recebida: " + nmeastr);

  // Percorre a mensagem atraves das vírgulas
  int commaCount = 0;
  char* piece = strtok(NULL, ",");
  String cota;


  // Percorre a mensagem até encontrar a nona vírgula
  while (piece != NULL) {
    commaCount++;

    switch (commaCount){
      // Altitude é o nono elemento da mensagem, altitute nivel do mar
      case 9:
        cota = String(piece);
        break;

      // Verifica se a mensagem é válida
      case 10:
        if (piece[0] != 'M'){ return "-1.00"; }               // Retorna uma altitude inválida se a mensagem não for válida
        break;
          
      // Diferença é o décimo primeiro elemento da mensagem, diferença entre a altitude elipsoidal e a altitude nivel do mar
      case 11:
        cota = String(cota.toFloat() + String(piece).toFloat(), 3);
        return cota;                                          // Retorna a cota elipsoidal
        break;
        
      default:
        break;
    }

    piece = strtok(NULL, ",");                                // Pega o próximo elemento da mensagem
  }

  return "-1.00";                                             // Retorna uma altitude inválida se não encontrar a nona vírgula
}






#endif // ZEDHANDLER_H