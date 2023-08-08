#ifndef SERVER_H
#define SERVER_H

// Este arquivo contém as funções para configurar o servidor web,
// enviar requisições dos arquivos do servidor web e receber requisições do cliente.



// Função para configurar o servidor web.
void setupServer() {
  // Funções para configurar as rotas do servidor web e os arquivos do servidor web.
  setupServerPages();
  setupServerStyles();
  setupServerScripts();

  

  
  // ========== Rotas de funções do servidor web ==========


  // Rota para cancelar a pesquisa realizada pelo escravo.
  server.on("/pararTrabalho", HTTP_GET, [](AsyncWebServerRequest *request){
    printString("\n\n##### Requisicao Recebida: /pararTrabalho");

    comandoEscravo = PARAR_TRABALHO;
   
    request->send(200, "text/plain", "Cancelando pesquisa...");
  });
  

// Rota para receber dados do cliente em formato JSON.
  AsyncCallbackJsonWebHandler* postConfig = new AsyncCallbackJsonWebHandler("/postConfiguration",
  [](AsyncWebServerRequest *request, JsonVariant &json) {
    printString("\n\n##### Requisicao Recebida: /postConfiguration");

    // Receber o JSON do cliente
    // jsonObj = json.as<JsonObject>();
    printString("Received JSON object:");
    printJson(json);
    printString("");

    // Configurar o proximo comando a ser enviado para o escravo
    if(escravoTrabalhando){
      printString("Escravo trabalhando");
      proximoComandoEscravo = NOVO_TRABALHO;
      mensagemStrAux = json.as<String>();
    } else{
      printString("Escravo nao trabalhando");
      comandoEscravo = NOVO_TRABALHO;
      mensagemStr = json.as<String>();
    }
    
    request->send(200, "text/plain", "Recebendo configuracao...");
  });



  //  Rota para salvar um novo ponto de interesse.
  AsyncCallbackJsonWebHandler* novoPonto = new AsyncCallbackJsonWebHandler("/novoPonto",
  [](AsyncWebServerRequest *request, JsonVariant &json) {

    printString("\n\n##### Requisicao Recebida: /novoPonto");

    printString("Received JSON object:");
    printJson(json);
    printString("");


    // Configurar o proximo comando a ser enviado para o escravo
    if(escravoTrabalhando){
      printString("Escravo trabalhando");
      proximoComandoEscravo = NOVO_PONTO;
      mensagemStrAux = json.as<String>();
    } else{
      printString("Escravo nao trabalhando");
      comandoEscravo = NOVO_PONTO;
      mensagemStr = json.as<String>();
    }
   
    request->send(200, "text/plain", "Salvando novo ponto...");
  });

  
  // Adicionar a rotas de funções do servidor web.
  server.addHandler(postConfig);
  server.addHandler(novoPonto);

  
  //  Rota para salvar um novo ponto de interesse.
  server.on("/getStatus", HTTP_GET, [](AsyncWebServerRequest *request){
    printString("\n\n##### Requisicao Recebida: /getStatus");
    printStringNoBreak("Enviando Status: ");

    String statusStr;

    switch (statusAtual){
    case ESPERANDO:
      statusStr = "Esperando";
      break;

    case TRABALHANDO:
      statusStr = "Trabalhando";
      break;
    
    default:
      break;
    }
    
    printString(statusStr);
    request->send(200, "text/plain", statusStr);
  });


// Rota para receber a lista de arquivos do escravo.
  server.on("/getFiles", HTTP_GET, [](AsyncWebServerRequest *request){
    printString("\n\n##### Requisicao Recebida: /getFiles");
    printString("Enviando lista de arquivos...");
    printString(listaArquivosStr);

    request->send(200, "application/json", listaArquivosStr);
  });

  
// Rota para definir a cota de referência.
  server.on("/cotaReferencia", HTTP_POST, [](AsyncWebServerRequest *request){
    printString("\n\n##### Requisicao Recebida: /cotaReferencia");
    printString("Definindo cota de referencia...");


    // Define a cota de referência com base no ponto recebido, com uma margem de erro.
    cotaRefInferior = request->getParam("Ponto")->value().toFloat() - MARGEM_COTA_REFERENCIA / 100.0;
    cotaRefSuperior = request->getParam("Ponto")->value().toFloat() + MARGEM_COTA_REFERENCIA / 100.0;


    request->send(200, "text/plain", "Definindo cota de referencia...");
  });



// Rota para receber a lista de arquivos do escravo.
  server.on("/getPontos", HTTP_GET, [](AsyncWebServerRequest *request){
    printString("\n\n##### Requisicao Recebida: /getPontos");
    printString("Enviando lista de pontos...");
    printString(listaPontos);

    if (listaPontos == "") 
      request->send(204, "application/json", "Nenhum ponto salvo.");
    else
      request->send(200, "application/json", listaPontos);

  });
}


#endif