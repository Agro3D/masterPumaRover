//Página de estilos da página inicial do servidor
char INDEX_STYLE[] PROGMEM = R"=====(

.titulo{
    font-size: 2vh;
    font-weight: bold;
    padding-left: 1vh;
}

#options{
    padding-bottom: 3vh;
    margin-bottom: 0;
}

#configuracaoRadio{
    column-count: 2;
    display: flex;
    align-items: center;
    justify-content: space-around;
    padding-bottom: 3vh;
}

#frequence{
    height: 3vh;
    width: 40%;
}

#frequenciaValor{
    display: flex;
    align-items: center;
    justify-content: center;
}

#frequenciaValor input{
    margin-right: 1vh;
}

.optionsDivs{
    display: flex;
    flex-direction: column;
    height: auto;
    margin-bottom: 10px;
}

.optionsRadio{
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    padding: 1vh;
}

.input{
    margin: 0.3vh 0vh 0vh 0.6vh;
    width: 60%;
    height: 2.5vh;
    border-radius: 8px;
}

.button{
    display: flex;
    align-items: center;
    justify-content: center;
    margin-top: 1vh;
}


#checkboxsOptions{
 column-count: 2;
}

#botaoNovoTrabalho{
    width: 16vw;
    height: 4.5vh;
    border-radius: 10px;
    background-color: #65c55c;
    font-weight: bold;
    font-size: 2vh;
    margin: 1.5vh 0;
}

#botaoNovoTrabalho:hover{
    background-color: #4e9e44;
    cursor: pointer;
}

#botaoCancelar{
    background-color: #a011ff;
    width: 16vw;
    height: 4.5vh;
    border-radius: 10px;
    font-size: 2vh;
    font-weight: bold;
    margin: 1.5vh 0;
}

#botaoCancelar:hover{
    background-color: #810ad1;
    cursor: pointer;
}

#constelacoesOptions{
    column-count: 2;
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
    font-size: 12vh;
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
    justify-content: center;
    padding: 1vh; 
    font-size: 2.5vh;
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

.visivel{
    display: block;
}

.naoVisivel{
    display: none;
}

/* 
320px — 480px: Mobile devices
481px — 768px: iPads, Tablets
769px — 1024px: Small screens, laptops
1025px — 1200px: Desktops, large screens
1201px and more —  Extra large screens, TV
 */


@media (max-width: 850px) {
    
    #checkboxsOptions{
        column-count: 1;
    }

    #cotaQuadro{
        padding-top: 0;
        padding-bottom: 0;
        margin-block: 0;
    }
}

)=====";
