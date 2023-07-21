#ifndef ZEDHANDLER_H
#define ZEDHANDLER_H


String getAltitudeFromNMEA(String nmeastr);

// Função para receber e processar a mensagem do cliente.
void processaMensagem(String message){

    
    String cota = getAltitudeFromNMEA(message);
    if(cota != "-1.00"){

      Serial.println();
      Serial.println("Cota: " + String(cota));
      webSocket.broadcastTXT("{\"Mensagem\": \"Cota\", \"Valor\": " + String(cota) + "}");
  }
}




// Função para pegar a cota do GPS
String getAltitudeFromNMEA(String nmeastr) {
    char* nmea = (char*) nmeastr.c_str();

    // Divide a string em substrings separadas por vírgula
    nmea = strtok(nmea, ",");

    // Verifica se a mensagem é do tipo GNGGA
    if (strcmp(nmea, "$GNGGA") != 0) {
        return "-1.00";     // Retorna uma altitude inválida se a mensagem não for do tipo GNGGA
    }

    Serial.print("Mensagem GNGGA recebida: " + nmeastr);


    // Conta a quantidade de vírgulas na mensagem
    int commaCount = 0;
    char* piece = strtok(NULL, ",");
    String cota;

    // Percorre a mensagem até encontrar a nona vírgula
    while (piece != NULL) {
        commaCount++;

        // Altitude é o nono elemento da mensagem

        switch (commaCount)
        {
        case 9:
            cota = String(piece);
            break;
        case 10:
            if (piece[0] != 'M'){
                return "-1.00";
            }
            break;
        case 11:
            cota = String(cota.toFloat() + String(piece).toFloat(), 3);
            return cota;
        
        default:
            break;
        }
        
        piece = strtok(NULL, ",");
    }

    return "-1.00";     // Retorna uma altitude inválida se não encontrar a nona vírgula
}






#endif // ZEDHANDLER_H