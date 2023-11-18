//Página de estilos do popup fixo de avisos
char POPUP_FIX_STYLE[] PROGMEM = R"=====(

:root {
    --marginTop: 0;
    --largura: 0;
    --left: 0;
  }
  
  /* CSS para alert Message */
  .messageFix {
    --marginTop: 20vh;
    --largura: 40%;
    --left: 76%;
    visibility: hidden;
    margin: 10px auto;
    background-color: #a011ff;
    color: white;
    text-align: center;
    border-radius: 10px;
    padding: 3vh;
    position: fixed;
    z-index: 100;
    width: var(--largura);
    left: var(--left);
    /* top: 20vh; */
    top: var(--marginTop);
    font-size: 1rem;
    font-weight: bold;
    transform: translate(-50%, -50%);
  }
  
  .closebtn{
    margin-left: 15px;
    color: white;
    font-weight: bold;
    float: right;
    font-size: 1.5rem;
    line-height: 20px;
    cursor: pointer;
    transition: 0.3s;
  }
  
  .closebtn:hover{
    color: black;
  }
    
  /* A mensagem aparece (pode personalizar como preferir) */
  .messageFix.show {
    visibility: visible;
    -webkit-animation: fadeInAlertMessage 0.6s;
    animation: fadeInAlertMessage 0.6s;
  }
  
  .messageFix.hide{
    visibility: visible;
    -webkit-animation: fadeOutAlertNessage 0.6s 0.1s forwards;
    animation: fadeOutAlertNessage 0.6s 0.1s forwards;
  }
  
    
  @-webkit-keyframes fadeInAlertMessage {
    from {top: 0; opacity: 0;} 
    to {top: var(--marginTop); opacity: 1;}
  }
    
  @keyframes fadeInAlertMessage {
    from {top: 0; opacity: 0;}
    to {top: var(--marginTop); opacity: 1;}
  }
    
  @-webkit-keyframes fadeOutAlertNessage {
    from {top: var(--marginTop); opacity: 1;} 
    to {top: 0; opacity: 0;}
  }
    
  @keyframes fadeOutAlertNessage {
    from {top: var(--marginTop); opacity: 1;}
    to {top: 0; opacity: 0;}
  }
  
  
  @media only screen and (max-width: 800px) {
    .messageFix {
      --marginTop: 15vh;
      --largura: 60%;
      --left: 67%;
      padding: 1vh;
    }
  }
  
  
  @media only screen and (max-width: 600px) {
    .messageFix {
      --marginTop: 17vh;
      --largura: 45%;
      --left: 0%;
      padding: 1vh;
      left: 76%;
      font-size: 0.8rem;
    }
  }

)=====";
