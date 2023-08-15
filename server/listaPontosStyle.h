//Página de estilos da lista de pontos
char LISTA_PONTOS_STYLE[] PROGMEM = R"=====(

:root {
    --alturaExpandirInicial: 0;
    --alturaExpandirFinal: 0;
    --alturaRecolherInicial: 0;
    --alturaRecolherFinal: 0;
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
    flex-direction: column;
    align-items: flex-start;
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


.pontoDescricao{
    font-size: 0.8rem;
    display: none;
    animation: fadein 2s;
}

@keyframes fadein {
    from { opacity: 0; }
    to   { opacity: 1; }
}

.expandir{
    animation: expandir 0.5s;
}

@keyframes expandir {
    from { height: var(--alturaExpandirInicial); }
    to   { height: var(--alturaExpandirFinal); }
}

.recolher{
    animation: recolher 0.5s;
}

@keyframes recolher {
    from { height: var(--alturaRecolherInicial); }
    to   { height: var(--alturaRecolherFinal); }
}

)=====";
