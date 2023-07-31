//Página de estilos da página inicial do servidor
char INDEX_STATUS_STYLE[] PROGMEM = R"=====(

.titulo{
    font-size: 2vh;
    font-weight: bold;
    padding-left: 1vh;
}

.button{
    display: flex;
    align-items: center;
    justify-content: center;
    margin-top: 1vh;
}

#botaoCancelar{
    background-color: #a011ff;
    width: 16vw;
    height: 4.5vh;
    border-radius: 10px;
    font-size: 2.6vh;
    font-weight: bold;
    margin: 1.5vh 0;
}

#botaoCancelar:hover{
    background-color: #810ad1;
    cursor: pointer;
}

#botaoNovoPonto{
    background-color: #65c55c;
    min-width: 16vw;
    height: 4.5vh;
    border-radius: 10px;
    font-size: 2.6vh;
    font-weight: bold;
    margin: 1.5vh 0;
}

#botaoNovoPonto:hover{
    background-color: #4e9e44;
    cursor: pointer;
}


#tituloCota{
    font-size: 6vh;
    font-weight: bold;
    margin-left: 5vh;
    margin-bottom: 2vh;
}

#cotaQuadro{
    display: flex;
    align-items: center;
    justify-content: center;
    padding: 1vh;
    border: 4px solid gray;
    border-radius: 5px;
    margin-inline: 5vh;
    margin-bottom: 2vh;
    background-color: #050505;
}

#cotaValor{
    margin-block: 1vh;
    color: #FFF;
    font-size: 14vw;
    font-weight: bold;
    font-family: Impact, Haettenschweiler, 'Arial Narrow Bold', sans-serif;
    letter-spacing: 0.8vh;
}

#informacoes{
    column-count: 2;
    margin-bottom: 2vh;
}

.informacoesDivs{
    display: flex;
    align-items: center;
    justify-content: space-around;
    padding: 1vh;
    font-size: 4vw;
    padding: 0.2vh;
}

.informacoesTitulos{
    font-weight: bold;
    margin-right: 2vh;
}

.informacoesValor{
    display: flex;
    align-items: center;
    justify-content: center;
    font-weight: bold;
    min-width: 20%;
    height: 5vh;
    border-radius: 5px;
}

#listaPontos{
    margin: 2vw;
    padding: 1vw;
    border: 1px solid #bbb;
    border-radius: 5px;
    background-color: #fff;
    box-shadow: 0px 0px 5px #bbb;  
    color: #000; 
}

.ponto{
    display: flex;
    align-items: center;
    justify-content: space-between;
    margin: 1vh;
    padding: 1vh;
    border: 1px solid #bbb;
    border-radius: 5px;
    background-color: #fff;
    box-shadow: 0px 0px 5px #bbb;  
    color: #000; 
}

.pontoNome{
    font-weight: bold;
    font-size: 1rem;
}



.verde{
    background-color: #2e8326;
    color: white;
}

.amarelo{
    background-color: #ffdb11;
    color: black;
}

.vermelho{
    background-color: #e81e1e;
    color: white;
}


.disabled {
    border: 1px solid #999999 !important;
    background-color: #cccccc !important;
    color: #666666 !important;
    cursor: default !important;
  }

/* 
320px — 480px: Mobile devices
481px — 768px: iPads, Tablets
769px — 1024px: Small screens, laptops
1025px — 1200px: Desktops, large screens
1201px and more —  Extra large screens, TV
 */


@media (max-width: 850px) {

    #cotaQuadro{
        padding-top: 0;
        padding-bottom: 0;
        margin-block: 0;
    }
}

)=====";