#ifndef DUALCOREHANDLER_H
#define DUALCOREHANDLER_H


void ProcessCoreLoop(void *arg) {
  while(1){

    // Lê as mensagens recebidas do ZED
    while (MySerialZed.available()) {
      String message = MySerialZed.readStringUntil('\n');
      
      // Caso esteja trabalhando, processa a mensagem recebida.
      if(receberMensagens){
        processaMensagem(message);
      }
    }


    // Verifica o uso de memória do ESP32 e imprime um aviso caso o uso de memória tenha aumentado.
    static uint32_t lastHeapSize = 0;
    uint32_t currentHeapSize = ESP.getFreeHeap();
    
    // Caso o tamanho da memória tenha diminuido desde a última iteração do loop, imprime um aviso.
    if (currentHeapSize < lastHeapSize) {
      printStringNoBreak("WARNING: Heap size changed! Current heap size: ");
      printString(String(currentHeapSize));
    }

    // Atualiza o tamanho da memória da última iteração do loop.
    lastHeapSize = currentHeapSize;

    if(millis() - lastHeapSend > HEAP_SIZE_TIMER){
      lastHeapSend = millis();
      heapSize = String(currentHeapSize);
    }


    delay(300); 
  }
}


void CommCoreLoop(void *arg) {
  while(1){
    
    // Verifica se ha alguma requisicao do cliente, caso haja, processa e envia a requisicao para o escravo.
    if(comandoEscravo != -1) { slaveSendHandler(); }
    
    // Verifica se ha alguma mensagem do escravo, caso haja, processa a mensagem recebida.
    if(MySerial.available()) { slaveReceiveHandler(); }

  
    delay(200);
  }
}







#endif // DUALCOREHENDLER_H