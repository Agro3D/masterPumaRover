//Página de estilos das torres de sinal do radio
char SINAL_RADIO_STYLE[] PROGMEM = R"=====(

#sinalRadio{
    width: 60px;
    height: 80px;
    position: absolute;
    right: 15px;
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
    border: 2px solid #555;
    border-radius: 6px 6px 0px 0px;
}

#sinalRadioTorre4{
    width: 15%;
    height: 80%;
    border: 2px solid #555;
    border-radius: 6px 6px 0px 0px;
}

.comTorre{
    background-color: aliceblue;
}

.semTorre{
    background-color: #555;
}

)=====";
