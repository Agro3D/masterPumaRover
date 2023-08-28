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
  
  PontoStr.replace("\\n", "<br />");
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
}


// Funçaõ para adiciona novo comando na fila de comandos a serem enviados para o escravo
void novoComando(int novoComando, String novaMensagem){
  printFuncCore(__func__);

  printString("Comando Atual: " + String(comandoEscravo));
  printString("Lista de Comandos: " + String(listaComandos.size()));

  // Caso o comando atual seja -1 e a lista de comandos esteja vazia, o comando atual é o novo comando
  if(comandoEscravo == -1 && listaComandos.size() == 0){
    comandoEscravo = novoComando;
    mensagemStr = novaMensagem;
  }else{
    // Caso o haja algum comando na lista de comandos ou um comando atual, o novo comando é adicionado na lista de comandos
    listaComandos.push_back(novoComando);
    listaMensagens.push_back(novaMensagem);


    // Caso haja comandos repetidos na lista de comandos, eles são removidos
    if(listaComandos.size() > 1){

      // Caso o novo comando seja um GET_STATUS, ele remove os GET_STATUS anteriores
      if(novoComando == GET_STATUS){
        for (int i = 0; i < listaComandos.size()-1; i++){
          if(listaComandos[i] == GET_STATUS){
            listaComandos.erase(listaComandos.begin() + i);
            listaMensagens.erase(listaMensagens.begin() + i);
          }
        }
        
      // Caso o novo comando seja um PARAR_TRABLHO, ele remove os LISTAR_PONTOS anteriores
      }else if(novoComando == PARAR_TRABALHO){
        for (int i = 0; i < listaComandos.size()-1; i++){
          if(listaComandos[i] == LISTAR_PONTOS){
            listaComandos.erase(listaComandos.begin() + i);
            listaMensagens.erase(listaMensagens.begin() + i);
          }
        }

      // Caso o novo comando seja um NOVO_TRABALHO, ele remove os LISTAR_ARQUIVOS anteriores
      } else if(novoComando == NOVO_TRABALHO){
        for (int i = 0; i < listaComandos.size()-1; i++){
          if(listaComandos[i] == LISTAR_ARQUIVOS){
            listaComandos.erase(listaComandos.begin() + i);
            listaMensagens.erase(listaMensagens.begin() + i);
          }
        }
      }
    }
  }
}


// Função para executar o próximo comando da lista de comandos
void proximoComando(){
  
  // Caso haja heapSize, envia o heapSize para o escravo antes de enviar o próximo comando
  if(heapSize != ""){
    comandoEscravo = HEAP_SIZE;
    mensagemStr = heapSize;
    heapSize = "";
    return;
  }

  printString("Lista de Comandos: " + String(listaComandos.size()));
  // Caso a lista de comandos esteja vazia, o comando atual é -1
  if(listaComandos.size() == 0){
    comandoEscravo = -1;
    mensagemStr = "";
    return;

  }else{
    // Caso haja algum comando na lista de comandos, o próximo comando é o primeiro da lista
    comandoEscravo = listaComandos[0];
    mensagemStr = listaMensagens[0];

    // Remove o primeiro comando da lista de comandos
    listaComandos.erase(listaComandos.begin());
    listaMensagens.erase(listaMensagens.begin());
  }
}


// Função para imprimir a lista de comandos
void printListaComandos(){
  printFuncCore(__func__);

  printString("Lista de Comandos: ");
  printString("Quantidade: " + String(listaComandos.size()));

  for(int i = 0; i < listaComandos.size(); i++){
    printString("Comando: " + String(listaComandos[i]));
  }
}


// Função para imprimir o nucleo que está executando a função
void printFuncCore(String func){

  Serial.println("==================================================");
  Serial.print(func);
  Serial.print(" : ");
  Serial.print(xTaskGetTickCount());
  Serial.print(" : ");
  Serial.print("This loop runs on ");
  Serial.print(xPortGetCoreID() ? "APP_CPU" : "PRO_CPU");
  Serial.println("(" + String(xPortGetCoreID()) + ") core.");
  Serial.println("==================================================");
}

#endif // UTILS_H