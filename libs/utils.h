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


// Função para adicionar um novo ponto na lista de pontos
void novoPonto(String PontoStr) {
  DynamicJsonDocument Ponto(512);
  deserializeJson(Ponto, PontoStr);

  if(listaPontos == "" || listaPontos == "\"\"" || listaPontos == NULL){
    listaPontos = "{\"Pontos\":[{\"Ponto\":\"" + Ponto["Ponto"].as<String>() + "\", \"Descricao\":\"" + Ponto["Descricao"].as<String>() + "\"}]}";
  }else{
    // Encontrar a posição do último ']'
    int pos = listaPontos.lastIndexOf(']');

    // Inserir a nova string de ponto na posição encontrada
    listaPontos = listaPontos.substring(0, pos) +
    ", {\"Ponto\":\"" + Ponto["Ponto"].as<String>() +
    "\", \"Descricao\":\"" + Ponto["Descricao"].as<String>() + "\"}" +
    listaPontos.substring(pos);
  }
  listaPontos.replace("\\n", "</br>");
}




#endif // UTILS_H