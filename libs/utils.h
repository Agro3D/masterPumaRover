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

  if(listaPontos.as<String>() == "" || listaPontos.as<String>() == "\"\"" || listaPontos.as<String>() == NULL){
    String novoPonto = "{\"Pontos\":[" + PontoStr + "]}";
    deserializeJson(listaPontos, novoPonto);
  }else{
  DynamicJsonDocument Ponto(512);
  deserializeJson(Ponto, PontoStr);

  listaPontos["Pontos"].add(Ponto);
  }
}


// Funçaõ para adiciona novo comando na fila de comandos a serem enviados para o escravo
void novoComando(int novoComando, String novaMensagem){

  printString("Comando Atual: " + String(comandoEscravo));
  printString("Lista de Comandos: " + String(listaComandos.size()));

  // Caso o comando atual seja -1 e a lista de comandos esteja vazia, o comando atual é o novo comando
  if(comandoEscravo == -1 && listaComandos.size() == 0){
    comandoEscravo = novoComando;
    mensagemStr = novaMensagem;
  }else{
    // Caso o haja algum comando na lista de comandos ou um comando atual, o novo comando é adicionado na lista de comandos

    // Caso a lista de comandos esteja vazia, o comando atual é duplicado na lista de comandos
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
    comandoBackup = HEAP_SIZE;
    mensagemStrBackup = heapSize;
    return;
  }

  printString("Lista de Comandos: " + String(listaComandos.size()));
  // Caso a lista de comandos esteja vazia, o comando atual é -1
  if(listaComandos.size() == 0){
    comandoEscravo = -1;
    mensagemStr = "";
    comandoBackup = -1;
    mensagemStrBackup = "";
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


// Reenvia o ultimo comando para o escravo
void reenviaUltimoComando(){
  comandoEscravo = comandoBackup;
  mensagemStr = mensagemStrBackup;
}


// Função para imprimir a lista de comandos
void printListaComandos(){

  printString("Lista de Comandos: ");
  printString("Quantidade: " + String(listaComandos.size()));

  for(int i = 0; i < listaComandos.size(); i++){
    printString("Comando: " + String(listaComandos[i]));
  }
}


// Função para imprimir o nucleo que está executando a função
// Exemplo de uso: printFuncCore(__func__);
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


// Função para imprimir a quantidade de memoria usada
void printStackCore(String func){
  UBaseType_t stackLeft = STACK_SIZE_CPU - uxTaskGetStackHighWaterMark(NULL);
  printStringNoBreak(func);
  printStringNoBreak(" - stack used: ");
  printString(String(stackLeft));
}


// Função para converter graus e minutos para graus decimais
String converterGrausDecimais(int graus, float minutos){
  String grausDecimais = String(graus + (minutos/60), 8) + "º";
  return grausDecimais;
}


// Atualizar sinal de rádio no servidor
void atualizaSinalRadio(int sinalRadio){
    Serial.println("Sinal de radio: " + String(sinalRadio));

    if(sinalRadio){
      webSocket.broadcastTXT("{\"Mensagem\": \"SINAL_RADIO\", \"Valor\": 4}");
    }else{
      webSocket.broadcastTXT("{\"Mensagem\": \"SINAL_RADIO\", \"Valor\": 0}");
    }
}


// Função atribuir cota de referência
void setCotaReferencia(float cota){
  cotaRef = cota;
  cotaRefInferior = cotaRef - MARGEM_COTA_REFERENCIA / 100.0;
  cotaRefSuperior = cotaRef + MARGEM_COTA_REFERENCIA / 100.0;

  webSocket.broadcastTXT("{\"Mensagem\": \"COTA_REFERENCIA\", \"Valor\": " + String(cotaRef, 3) + "}");
}




#endif // UTILS_H