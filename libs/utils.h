#ifndef UTILS_H
#define UTILS_H

// Este arquivo contém as funções diversas para auxiliar o código



// Função para imprimir uma string na serial, apenas se o DEBUG estiver ativado
void printString(String message){
  if (DEBUG){
    Serial.println(message);
  }
}



// Função para imprimir uma string na serial sem quebrar a linha, apenas se o DEBUG estiver ativado
void printStringNoBreak(String message){
  if (DEBUG){
    Serial.print(message);
  }
}


// Função para imprimir um JSON na serial, apenas se o DEBUG estiver ativado
void printJson(DynamicJsonDocument doc){
  if (DEBUG){
    serializeJsonPretty(doc, Serial);
    Serial.println();
  }
}



#endif // UTILS_H