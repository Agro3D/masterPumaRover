#ifndef SERVER_SCRIPTS_H
#define SERVER_SCRIPTS_H


// Este arquivo contém as requisições e respostas dos scripts JS do servidor web.


// Função para responder as requisições dos scripts JS do servidor web.
void setupServerScripts(){

// ========== Rotas dos scripts do servidor web ==========
  // Rota para o script JS global do servidor web.
  server.on("/scripts/global.js", HTTP_GET, [](AsyncWebServerRequest *request){
    printString("\n\n##### Requisicao Recebida: /scripts/global.js");
    printString("Enviando script.js ...");
    request->send(200, "text/javascript", GLOBAL_SCRIPT);
  });


  // Rota para o script JS de configuração da pagina inicial.
  server.on("/scripts/indexConfig.js", HTTP_GET, [](AsyncWebServerRequest *request){
    printString("\n\n##### Requisicao Recebida: /scripts/indexConfig.js");
    printString("Enviando scriptConfig.js ...");
    request->send(200, "text/javascript", INDEX_CONFIG_SCRIPT);
  });


  // Rota para o script JS de status da pagina inicial.
  server.on("/scripts/indexStatus.js", HTTP_GET, [](AsyncWebServerRequest *request){
    printString("\n\n##### Requisicao Recebida: /scripts/indexStatus.js");
    printString("Enviando scriptStatus.js ...");
    request->send(200, "text/javascript", INDEX_STATUS_SCRIPT);
  });


  // Rota para o script JS da página de pontos.
  server.on("/scripts/pontos.js", HTTP_GET, [](AsyncWebServerRequest *request){
    printString("\n\n##### Requisicao Recebida: /scripts/pontos.js");
    printString("Enviando script.js ...");
    request->send(200, "text/javascript", PONTOS_SCRIPT);
  });


  // Rota para o script JS do WebSocket
  server.on("/scripts/webSocket.js", HTTP_GET, [](AsyncWebServerRequest *request){
    printString("\n\n##### Requisicao Recebida: /scripts/webSocket.js");
    printString("Enviando webSocket.js ...");
    request->send(200, "text/javascript", WEBSOCKET_SCRIPT);
  });



}

#endif // SERVER_SCRIPTS_H