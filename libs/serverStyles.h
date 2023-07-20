#ifndef SERVER_STYLES_H
#define SERVER_STYLES_H


void setupServerStyles(){

// ========== Rotas dos estilos do servidor web ==========
  // Rota para o estilo CSS da página inicial. (globalStyle.css)
  server.on("/styles/global.css", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /styles/global.css");
    Serial.println("Enviando style.css ...");
    request->send(200, "text/css", GLOBAL_STYLE);
  });


  // Rota para o estilo CSS do header. (headerStyle.css)
  server.on("/styles/header.css", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /styles/header.css");
    Serial.println("Enviando headerStyle.css ...");
    request->send(200, "text/css", HEADER_STYLE);
  });


  // Rota para o estilo CSS da página inicial. (indexConfigStyle.css)
  server.on("/styles/index.css", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /styles/index.css");
    Serial.println("Enviando indexConfigStyle.css ...");
    request->send(200, "text/css", INDEX_CONFIG_STYLE);
  });


  // Rota para o estilo CSS da página inicial. (indexStatusStyle.css)
  server.on("/styles/index.css", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /styles/index.css");
    Serial.println("Enviando indexStatusStyle.css ...");
    request->send(200, "text/css", INDEX_STATUS_STYLE);
  });


  // Rota para o estilo CSS da página de arquivos. (arquivosStyle.css)
  server.on("/styles/arquivos.css", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /styles/arquivos.css");
    Serial.println("Enviando arquivosStyle.css ...");
    request->send(200, "text/css", ARQUIVOS_STYLE);
  });


}

#endif // SERVER_STYLES_H