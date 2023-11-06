//Página de estilos das torres de sinal do radio
char SINAL_RADIO_STYLE[] PROGMEM = R"=====(

#sinalRadio{
    width: calc(0.8 * 8vh);
    height: calc(0.8 * 8vh);
    position: absolute;
    right: 5px;
    display: flex;
    flex-direction: column;
    justify-content: space-between;
    align-items: center;
}

#torres{
    width: 100%;
    height: 80%;
    display: flex;
    justify-content: space-between;
    align-items: baseline;
}

#sinalRadioTorre1{
    width: 15%;
    height: 20%;
    border-radius: 8px 8px 0px 0px;
}

#sinalRadioTorre2{
    width: 15%;
    height: 40%;
    border-radius: 6px 6px 0px 0px;
}

#sinalRadioTorre3{
    width: 15%;
    height: 60%;
    border-radius: 6px 6px 0px 0px;
}

#sinalRadioTorre4{
    width: 15%;
    height: 80%;
    border-radius: 6px 6px 0px 0px;
}

.comTorre{
    background-color: aliceblue;
}

.semSinal{
    background-color: red;
}

.semTorre{
    background-color: #555;
}

@media (orientation: landscape){
    #sinalRadio{
        width: calc(0.9 * 10vh);
        height: calc(0.9 * 10vh);
    }
}

)=====";
