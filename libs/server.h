#ifndef SERVER_H
#define SERVER_H



void setupServer() {
  // Função para configurar o servidor web.
  setupServerPages();
  setupServerStyles();
  setupServerScripts();

  
  // ========== Rotas de funções do servidor web ==========


  // Rota para cancelar a pesquisa realizada pelo escravo.
  server.on("/pararTrabalho", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /pararTrabalho");

    ComandoEscravo = PARAR_TRABALHO;
   
    request->send(200, "text/plain", "Cancelando pesquisa...");
  });
  

// Rota para receber dados do cliente em formato JSON.
  AsyncCallbackJsonWebHandler* postConfig = new AsyncCallbackJsonWebHandler("/postConfiguration",
  [](AsyncWebServerRequest *request, JsonVariant &json) {
    Serial.println("\n\n##### Requisicao Recebida: /postConfiguration");

    // Receber o JSON do cliente
    // jsonObj = json.as<JsonObject>();
    Serial.println("Received JSON object:");
    serializeJsonPretty(json, Serial);

    mensagemStr = json.as<String>();

    ComandoEscravo = NOVO_TRABALHO;
    
    request->send(200, "text/plain", "Recebendo configuracao...");
  });



  //  Rota para salvar um novo ponto de interesse.
  AsyncCallbackJsonWebHandler* novoPonto = new AsyncCallbackJsonWebHandler("/novoPonto",
  [](AsyncWebServerRequest *request, JsonVariant &json) {

    Serial.println("\n\n##### Requisicao Recebida: /novoPonto");

    Serial.println("Received JSON object:");
    serializeJsonPretty(json, Serial);

    mensagemStr = json.as<String>();

    ComandoEscravo = NOVO_PONTO;
   
    request->send(200, "text/plain", "Salvando novo ponto...");
  });

  
  // Adicionar a rota ao servidor
  server.addHandler(postConfig);
  server.addHandler(novoPonto);

  
  //  Rota para salvar um novo ponto de interesse.
  server.on("/getStatus", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /getStatus");

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
    request->send(200, "text/plain", statusStr);
  });


// Rota para receber a lista de arquivos do escravo.
  server.on("/getFiles", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /getFiles");
    Serial.println("Enviando lista de arquivos...");
    Serial.println(listaArquivosStr);

    request->send(200, "application/json", listaArquivosStr);
  });
}


#endif