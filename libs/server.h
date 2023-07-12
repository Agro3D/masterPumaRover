#ifndef SERVER_H
#define SERVER_H



void setupServer() {
  // Função para configurar o servidor web.
  setupServerPages();
  setupServerStyles();
  setupServerScripts();

  
// ========== Rotas de funções do servidor web ==========


// Rota para receber dados do cliente em formato JSON.
  AsyncCallbackJsonWebHandler* newConfig = new AsyncCallbackJsonWebHandler("/postConfiguration",
  [](AsyncWebServerRequest *request, JsonVariant &json) {
    Serial.println("\n\n##### Requisicao Recebida: /postConfiguration");

    // Receber o JSON do cliente
    // jsonObj = json.as<JsonObject>();
    Serial.println("Received JSON object:");
    serializeJsonPretty(json, Serial);

    mensagemStr = json.as<String>();

    ComandoEscravo = NOVA_CONFIGURACAO;
    
    request->send(200, "text/plain", "Recebendo configuracao...");
  });
  // Adicionar a rota ao servidor
  server.addHandler(newConfig);
}


#endif