//Página de estilos do popup de novo ponto
char POPUP_NOVO_PONTO_STYLE[] PROGMEM = R"=====(

/* CSS para Popup */
.popup {
    display: none;
    position: fixed;
    z-index: 1;
    left: 0;
    width: 100vw;
    overflow: auto;
    -webkit-animation: fadeInPopup 0.6s;
    animation: fadeInPopup 0.6s;
}

@-webkit-keyframes fadeInPopup {
  from {top: 0; opacity: 0;} 
  to {bottom: 0; opacity: 1;}
}

@keyframes fadeInPopup {
  from {opacity: 0;}
  to {opacity: 1;}
}



/* popup Content */
.popup-content {
  bottom: 0;
  background-color: #292929;
  margin: 15% auto;
  padding: 20px;
  border: 2px solid #bbb;
  width: 50%;
  height: auto;
  border-radius: 10px;
  color: white;
  font-size: 0.8rem;
  font-weight: bold;
}


.inputPopup {
    width: 100%;
    height: 4vh;
    margin-top: 1vh;
    margin-bottom: 3vh;
    background-color: #f8f8f8;
    border: none;
    border-radius: 5px;
    border-bottom: 3px solid #fff;
    font-family: Verdana, Geneva, Tahoma, sans-serif;
}

.inputPopup:focus {
    outline: none;
    border-bottom: 3px solid #a011ff;
}

.textareaPopup {
    resize: none;
    height: 20vh;
}
    

#botoesPopup {
    display: flex;
    justify-content: space-around;
    align-items: center;
}

  
.botaoPopup {
    background-color: #27ae60; 
    border: none;
    color: white;
    padding: 10px 20px;
    text-align: center;
    text-decoration: none;
    display: inline-block;
    font-size: 14px;
    margin: 4px 2px;
    cursor: pointer;
    border-radius: 5px;
}
  
.botaoPopup:hover {
    background-color: #2b8f17; 
}
  
#cancel {
    background-color: #e74c3c; 
}
  
#cancel:hover {
    background-color: #c0392b; 
}



/* CSS para alert Message */
.message {
    visibility: hidden;
    margin: 10px auto;
    background-color: #a011ff;
    color: white;
    text-align: center;
    border-radius: 10px;
    padding: 3vh;
    position: fixed;
    z-index: 1;
    left: 50%;
    top: 10vh;
    font-size: 1rem;
    font-weight: bold;
    transform: translate(-50%, -50%);
  }
  
  /* A mensagem aparece (pode personalizar como preferir) */
  .message.show {
    visibility: visible;
    -webkit-animation: fadeInAlertMessage 0.6s, fadeOutAlertNessage 0.6s 2.5s;
    animation: fadeInAlertMessage 0.6s, fadeOutAlertNessage 0.6s 2.5s;
  }
  
  @-webkit-keyframes fadeInAlertMessage {
    from {top: 0; opacity: 0;} 
    to {top: 10vh; opacity: 1;}
  }
  
  @keyframes fadeInAlertMessage {
    from {top: 0; opacity: 0;}
    to {top: 10vh; opacity: 1;}
  }
  
  @-webkit-keyframes fadeOutAlertNessage {
    from {top: 10vh; opacity: 1;} 
    to {top: 0; opacity: 0;}
  }
  
  @keyframes fadeOutAlertNessage {
    from {top: 10vh; opacity: 1;}
    to {top: 0; opacity: 0;}
  }



/* CSS para dispositivos com largura de tela até 600px */
@media only screen and (max-width: 768px) {
    .popup-content {
      width: 85%;
    }
  
    /* Ajustar fontes para telas menores */
    input, textarea {
      font-size: 16px;
    }
  
    .botaoPopup {
      font-size: 18px;
    }
  
    .close {
      font-size: 24px;
    }
  
  }
  

)=====";
