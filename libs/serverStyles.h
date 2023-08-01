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
  server.on("/styles/indexConfig.css", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /styles/indexConfig.css");
    Serial.println("Enviando indexConfig.css ...");
    request->send(200, "text/css", INDEX_CONFIG_STYLE);
  });


  // Rota para o estilo CSS da página inicial. (indexStatusStyle.css)
  server.on("/styles/indexStatus.css", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /styles/indexStatus.css");
    Serial.println("Enviando indexStatus.css ...");
    request->send(200, "text/css", INDEX_STATUS_STYLE);
  });


  // Rota para o estilo CSS do popup de novo ponto. (popupAlertStyle.css)
  server.on("/styles/popupAlert.css", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /styles/popupAlert.css");
    Serial.println("Enviando popupAlert.css ...");
    request->send(200, "text/css", POPUP_NOVO_PONTO_STYLE);
  });


  // Rota para o estilo CSS da página de arquivos. (arquivosStyle.css)
  server.on("/styles/arquivos.css", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /styles/arquivos.css");
    Serial.println("Enviando arquivosStyle.css ...");
    request->send(200, "text/css", ARQUIVOS_STYLE);
  });


}

#endif // SERVER_STYLES_H