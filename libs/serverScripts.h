#ifndef SERVER_SCRIPTS_H
#define SERVER_SCRIPTS_H


void setupServerScripts(){

// ========== Rotas dos scripts do servidor web ==========
  // Rota para o script JS global do servidor web.
  server.on("/scripts/global.js", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /scripts/global.js");
    Serial.println("Enviando script.js ...");
    request->send(200, "text/javascript", GLOBAL_SCRIPT);
  });


  // Rota para o script JS da página inicial.
  server.on("/scripts/index.js", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /scripts/index.js");
    Serial.println("Enviando script.js ...");
    request->send(200, "text/javascript", INDEX_SCRIPT);
  });


  // Rota para o script JS da página inicial.
  server.on("/scripts/indexNewWork.js", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /scripts/indexNewWork.js");
    Serial.println("Enviando scriptNewWork.js ...");
    request->send(200, "text/javascript", INDEX_SCRIPTNEWWORK);
  });


  // Rota para o script JS da página de arquivos.
  server.on("/scripts/arquivos.js", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /scripts/arquivos.js");
    Serial.println("Enviando script.js ...");
    request->send(200, "text/javascript", ARQUIVOS_SCRIPT);
  });


  // Rota para o script JS do WebSocket
  server.on("/scripts/webSocket.js", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /scripts/webSocket.js");
    Serial.println("Enviando webSocket.js ...");
    request->send(200, "text/javascript", WEBSOCKET_SCRIPT);
  });



}

#endif // SERVER_SCRIPTS_H