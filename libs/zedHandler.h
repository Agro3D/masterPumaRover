#ifndef ZEDHANDLER_H
#define ZEDHANDLER_H

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
        if (commaCount == 9) {
            cota = String(piece);
        } else if (commaCount == 10)
        {
            if (piece[0] == 'M'){
                return cota;
            } else{
                return "-1.00";
            }
        }
        piece = strtok(NULL, ",");
    }

    return "-1.00";     // Retorna uma altitude inválida se não encontrar a nona vírgula
}


// Função para gerar uma cota aleatória
// int cotaInt = 630;
// String randomCota(){
//   // int randomNumber = random(628000, 633000); // generate a random integer between 680000 and 690000
//   // Min = 628 or cotaInt-1
//   int min = cotaInt-1;
//   // Max = 633 or cotaInt+1
//   int max = cotaInt+2;

//   if (min < 628) {
//     min = 628;
//   }
//   if (max > 633) {
//     max = 633;
//   }

//   Serial.println("Min: " + String(min));
//   Serial.println("Max: " + String(max));
  
//   cotaInt = random(min, max); // generate a random integer between 680000 and 690000
//   int cotaDecimal = random(0, 999); // generate a random integer between 0 and 999
//   int randomNumber = cotaInt*1000 + cotaDecimal; // generate a random integer between 680000 and 690000

//   Serial.println("Cota: " + String(cotaInt));
//   Serial.println("Decimal: " + String(cotaDecimal));

//   if (cotaDecimal < 10) {
//     cotaDecimal = cotaDecimal * 100;
//   } else if (cotaDecimal < 100) {
//     cotaDecimal = cotaDecimal * 10;
//   }
  

//   String randomNumberStr = String(cotaInt) + "." + String(cotaDecimal);

//   float randomFloat = randomNumber / 1000.00; // convert it to a float with 3 decimal places
//   return randomNumberStr;
// }





#endif // ZEDHANDLER_H