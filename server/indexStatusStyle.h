//Página de estilos da página inicial do servidor
char INDEX_STATUS_STYLE[] PROGMEM = R"=====(

.titulo{
    font-size: 2vh;
    font-weight: bold;
    padding-left: 1vh;
}

#botaoFinalizar{
    background-color: #41753c;
    color: white;
    padding: 1vh 3vw;
    border: 0;
    border-radius: 10px;
    font-size: 2.6vh;
    font-weight: bold;
}

#botaoFinalizar:hover{
    background-color: #4e9e44;
    cursor: pointer;
}

#botaoNovoPonto{
    background-color: #41753c;
    color: white;
    min-width: 16vw;
    height: 4.5vh;
    border: 0;
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
    display: flex;
    align-items: flex-end;
    width: 100%;
    font-size: 6vh;
    font-weight: bold;
    margin: 0;
}

#cotaQuadro{
    display: flex;
    flex-direction: column;
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
    margin-top: 0vh;
    margin-bottom: 1vh;
    color: #FFF;
    font-size: 14vw;
    font-weight: bold;
    font-family: Impact, Haettenschweiler, 'Arial Narrow Bold', sans-serif;
    letter-spacing: 0.8vh;
}

#informacoes{
    display: flex;
    margin-inline: 5vw;
    column-count: 2;
    margin-bottom: 2vh;
    justify-content: space-between;
}

#informacoesDiv{
    display: flex;
    flex-direction: column;
    justify-content: space-around;
}

.informacaoDiv{
    display: flex;
    align-items: center;
}

.informacoesTitulos{
    font-size: 4vw;
    font-weight: bold;
    margin-right: 2vh;
}

.informacoesValor{
    font-size: 3vw;
    display: flex;
    align-items: center;
    justify-content: center;
    font-weight: bold;
    min-width: 20%;
    border-radius: 5px;
}

#novoPonto{
    position: absolute;
    align-items: end;
    margin-left: 5vh;
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
    padding: 1vh;
}

.amarelo{
    background-color: #ffdb11;
    color: black;
    padding: 1vh;
}

.vermelho{
    background-color: #e81e1e;
    color: white;
    padding: 1vh;
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

    #tituloCota{
        font-size: 2.5vh;
    }

    #cotaValor{
        letter-spacing: 0.5vh;
        font-size: 12vw;
    }

    #botaoNovoPonto{
        width: 10vw;
        min-height: fit-content;
        font-size: 1.4vh;
        margin: 0;
    }

    #botaoFinalizar{
        font-size: 1.4vh;
        padding: 0.7vh 2.5vw;
    }

    #novoPonto{
        margin-left: 1vh;
    }

    .tituloMobile{
        font-size: 2.5vh !important;
    }
}

@media (orientation: landscape) and (max-height: 850px) {

    #tituloCota{
        font-size: 3.5vh;
    }

    #botaoNovoPonto{
        width: 6vw;
        min-height: fit-content;
        font-size: 3vh;
        margin: 3vh 0;
    }

    #botaoFinalizar{
        font-size: 3vh;
        padding: 3vh 4vw;
    }

    #novoPonto{
        margin-left: 1vh;
    }

    .tituloMobile{
        font-size: 6vh !important;
    }
}

)=====";
