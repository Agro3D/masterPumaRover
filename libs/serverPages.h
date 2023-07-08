#ifndef SERVER_PAGES_H
#define SERVER_PAGES_H


void setupServerPages() {
  // Função para configurar as páginas do servidor web.

  // Rota para erros 404 (página não encontrada).
  server.onNotFound([](AsyncWebServerRequest *request){

    // Mostrar a requisição recebida
    Serial.println("\n\n##### Requisicao NotFound Recebida:");
    Serial.println(request->url());
    Serial.println(request->methodToString());

    // Mostrar os argumentos da requisição recebida
    for (uint8_t i = 0; i < request->args(); i++) {
      Serial.printf("ARG[%s]: %s\n", request->argName(i).c_str(), request->arg(i).c_str());
    }

    // Mostrar o corpo da requisição recebida
    Serial.println("BODY:");
    Serial.println(request->contentType());
    Serial.println(request->contentLength());
    
    // Enviar uma resposta de erro 404
    request->send(404, "text/plain", "Page Not found");
  });




// ========== Rotas das paginas HTML do servidor web ==========
  // Rota para a página inicial do servidor web. (index.html & starting.html)
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /");
    
    Serial.println("Enviando index.html ...");
    request->send(200, "text/html", INDEX_PAGE);
  });


  // Rota para a página com o header do servidor web. (header.html)
  server.on("/header.html", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /header.html");
    Serial.println("Enviando header.html ...");
    request->send(200, "text/html", HEADER_PAGE);
  });


  // Rota para a página de arquivoss do servidor web. (arquivos.html)
  server.on("/arquivos.html", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("\n\n##### Requisicao Recebida: /arquivos.html");
    Serial.println("Enviando arquivos.html ...");
    request->send(200, "text/html", ARQUIVOS_PAGE);
  });
  

}

#endif // SERVER_PAGES_H