//Página de estilos da página inicial do servidor
char INDEX_CONFIG_STYLE[] PROGMEM = R"=====(

.titulo{
    font-size: 2vh;
    font-weight: bold;
    padding-left: 1vh;
}

#options{
    padding-bottom: 3vh;
    margin-bottom: 0;
}

#frequenceDiv{
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
}

#frequenceDiv select{
    width: 25%;
}

#configuracaoRadio{
    column-count: 2;
    display: flex;
    align-items: center;
    justify-content: space-around;
    padding-bottom: 3vh;
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

.inputSelect{
    height: 3vh;
}


.button{
    display: flex;
    align-items: center;
    justify-content: center;
    margin-top: 1vh;
}


#botaoNovaConfig{
    width: 16vw;
    height: 4.5vh;
    border-radius: 10px;
    background-color: #65c55c;
    font-weight: bold;
    font-size: 2vh;
    margin: 1.5vh 0;
}

#botaoNovaConfig:hover{
    background-color: #4e9e44;
    cursor: pointer;
}


#constelacoesOptions{
    column-count: 2;
    margin-bottom: 1vh;
}

#arquivos{
    display: flex;
    flex-direction: row;
    justify-content: space-around;
    margin-bottom: 1vh;
    font-size: 0.6rem;
    font-weight: bold;
}

.arquivosDivs{
    display: flex;
    flex-direction: column;
}

.inputContent{
    width: max-content;
}

#obs{
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    margin-bottom: 1vh;
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

)=====";
