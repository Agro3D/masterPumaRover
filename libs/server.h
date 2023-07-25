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
  AsyncCallbackJsonWebHandler* newConfig = new AsyncCallbackJsonWebHandler("/postConfiguration",
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

  // Adicionar a rota ao servidor
  server.addHandler(newConfig);


  
  //  Rota para salvar um novo ponto de interesse.
  server.on("/novoPonto", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /novoPonto");

    ComandoEscravo = NOVO_PONTO;
   
    request->send(200, "text/plain", "Salvando novo ponto...");
  });


  
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
}



#endif