#ifndef SERVER_STYLES_H
#define SERVER_STYLES_H


// Este arquivo contém as requisições e respostas dos estilos CSS do servidor web.



// Função para responder as requisições dos estilos CSS do servidor web.
void setupServerStyles(){

// ========== Rotas dos estilos do servidor web ==========
  // Rota para o estilo CSS da página inicial. (globalStyle.css)
  server.on("/styles/global.css", HTTP_GET, [](AsyncWebServerRequest *request){
    printString("\n\n##### Requisicao Recebida: /styles/global.css");
    printString("Enviando style.css ...");
    request->send(200, "text/css", GLOBAL_STYLE);
  });


  // Rota para o estilo CSS do header. (headerStyle.css)
  server.on("/styles/header.css", HTTP_GET, [](AsyncWebServerRequest *request){
    printString("\n\n##### Requisicao Recebida: /styles/header.css");
    printString("Enviando headerStyle.css ...");
    request->send(200, "text/css", HEADER_STYLE);
  });


  // Rota para o estilo CSS da página inicial. (indexConfigStyle.css)
  server.on("/styles/indexConfig.css", HTTP_GET, [](AsyncWebServerRequest *request){
    printString("\n\n##### Requisicao Recebida: /styles/indexConfig.css");
    printString("Enviando indexConfig.css ...");
    request->send(200, "text/css", INDEX_CONFIG_STYLE);
  });


  // Rota para o estilo CSS da página inicial. (indexStatusStyle.css)
  server.on("/styles/indexStatus.css", HTTP_GET, [](AsyncWebServerRequest *request){
    printString("\n\n##### Requisicao Recebida: /styles/indexStatus.css");
    printString("Enviando indexStatus.css ...");
    request->send(200, "text/css", INDEX_STATUS_STYLE);
  });


  // Rota para o estilo CSS da lista de pontos. (listaPontosStyle.css)
  server.on("/styles/listaPontos.css", HTTP_GET, [](AsyncWebServerRequest *request){
    printString("\n\n##### Requisicao Recebida: /styles/listaPontos.css");
    printString("Enviando listaPontos.css ...");
    request->send(200, "text/css", LISTA_PONTOS_STYLE);
  });


  // Rota para o estilo CSS do popup de novo ponto. (popupAlertStyle.css)
  server.on("/styles/popupAlert.css", HTTP_GET, [](AsyncWebServerRequest *request){
    printString("\n\n##### Requisicao Recebida: /styles/popupAlert.css");
    printString("Enviando popupAlert.css ...");
    request->send(200, "text/css", POPUP_NOVO_PONTO_STYLE);
  });


  // Rota para o estilo CSS da página de arquivos. (arquivosStyle.css)
  server.on("/styles/arquivos.css", HTTP_GET, [](AsyncWebServerRequest *request){
    printString("\n\n##### Requisicao Recebida: /styles/arquivos.css");
    printString("Enviando arquivosStyle.css ...");
    request->send(200, "text/css", ARQUIVOS_STYLE);
  });


}

#endif // SERVER_STYLES_H