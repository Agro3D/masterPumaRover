//Arquivo de estilos do servidor
char GLOBAL_STYLE[] PROGMEM = R"=====(
    
body{
    background-color: #838383;
    /* background: linear-gradient(to top, #00810b 0%, #141414 40%); */
    background-attachment: fixed;
    display: flex;
    flex-direction: column;
    align-items: center;
    min-width: 95vw;
    min-height: 100vh;
    margin: 0%;
    color: #FFF;
    font-size: 1.7vh;
    font-family: Verdana, Geneva, Tahoma, sans-serif
}

.divs{
    padding: 1vh 0;
    margin: -2px 1vh;
    background-color: #292929;
}

.bordas{
    border: 3px solid #872dc2;
    /* border: 3px solid #810ad17b; */
    border-left: 0;
    border-right: 0;
    border-bottom: 0;
}

#tituloPrincipal{
    text-align: center;
    font-size: 3.5vh;
    font-weight: bolder;
    margin-top: 1vh;
    margin-bottom: 2vh;
    color: #3a9732;
}

#body2{
    display: flex;
    flex-direction: column;
    border: 2px solid #616161;
    border-radius: 15px;
    min-width: 80vw;
    max-width: 95vw;
    margin-top: 10vh;
    margin-bottom: 4vh;
}

@media screen and (max-width: 400px){
    #body2{
        min-width: 75vw;
    }
}

@media (orientation: landscape) and (max-height: 850px){
    #tituloPrincipal{
        font-size: 6vh;
    }

    #body2{
        margin-top: 12vh;
    }
}

)=====";
