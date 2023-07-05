#ifndef SERVER_H
#define SERVER_H



void setupServer() {
  // Função para configurar o servidor web.
  setupServerPages();
  setupServerStyles();
  setupServerScripts();

  
// ========== Rotas de funções do servidor web ==========
  // Rota saber se a comunicação com o escravo está estabelecida.
  server.on("/getComunication", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /getComunication");
    if (hasComunication && serverStarted)
    {
      request->send(200, "text/plain", "Servidor iniciado e comunicacao com o escravo estabelecida.");
    }else{
      request->send(404, "text/plain", "Servidor nao iniciado ou comunicacao com o escravo nao estabelecida.");
    }
  });



  // Rota para verificar o status do trabalho realizada pelo escravo.
  server.on("/getStatus", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /getStatus");

    ComandoEscravo = GET_STATUS;
   
    request->send(200, "text/plain", "Verificando status do trabalho...");
  });



  // Rota para receber dados do cliente em formato JSON.
  AsyncCallbackJsonWebHandler* handler = new AsyncCallbackJsonWebHandler("/postConfiguration",
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
  server.addHandler(handler);



  // Rota para cancelar a pesquisa realizada pelo escravo.
  server.on("/cancelarPesquisa", HTTP_POST, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /cancelarPesquisa");

    ComandoEscravo = CANCELAR_PESQUISA;
   
    request->send(200, "text/plain", "Cancelando pesquisa...");
  });



  // Rota para cancelar o trabalho realizado pelo escravo.
  server.on("/cancelarProcesso", HTTP_POST, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /cancelarProcesso");

    ComandoEscravo = CANCELAR_TRABALHO;
   
    request->send(200, "text/plain", "Cancelando trabalho...");
  });



  // Rota para finalizar o trabalho realizado pelo escravo.
  server.on("/finalizarProcesso", HTTP_POST, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /finalizarProcesso");

    ComandoEscravo = FINALIZAR_TRABALHO;
   
    request->send(200, "text/plain", "Finalizando trabalho...");
  });



  // Rota para receber a lista de arquivos do escravo.
  server.on("/getFiles", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /getFiles");
    Serial.println("Enviando lista de arquivos...");
    Serial.println(listaArquivosStr);

    request->send(200, "application/json", listaArquivosStr);
  });


  // Rotas para exclusão de arquivos do escravo.
  server.on("/deleteFile", HTTP_POST, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /deleteFile");
    Serial.println("Enviando requisicao de exclusao de arquivo...");

    mensagemStr = "{\"Arquivo\":\""+ request->getParam("Arquivo")->value() + "\"}";
    ComandoEscravo = EXCLUIR_ARQUIVOS;
    
    request->send(200, "text/plain", "Enviando dados para o escravo...");
  });




// ========== Rotas de teste ==========
  // Rota de teste de envio de dados para o escravo. (TEMPORARIO)
  server.on("/teste", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /Teste");
    
    request->send(200, "text/html", TESTE);
  });

  // Rota de teste de envio de dados para o escravo. (TEMPORARIO)
  server.on("/sendDataTeste", HTTP_POST, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /sendDataTeste");

    // Enviar dados de parametros na url para o escravo
    Serial.println(request->url());
    Serial.println(request->params());
    
    mensagemStr = "{"+ request->getParam("Mensagem")->value() + "}";
    ComandoEscravo = request->getParam("Comando")->value().toInt();
    
    request->send(200, "text/plain", "Enviando dados para o escravo...");
  });


}


#endif