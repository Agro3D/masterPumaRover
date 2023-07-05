//Página inicial do servidor
char INDEX_PAGE[] PROGMEM = R"=====(
    
<!DOCTYPE html>
<html>
    <head>
        <title>Puma Station Web Server</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <meta charset="UTF-8">

        <link rel="stylesheet" type="text/css" href="styles/global.css">
        <link rel="stylesheet" type="text/css" href="styles/header.css">
        <link rel="stylesheet" type="text/css" href="styles/index.css">

        <script src="scripts/webSocket.js"></script>
        <script src="scripts/global.js"></script>
        <script src="scripts/index.js"></script>
    </head>

    <body onload="imports();startWebSocket();">
        <div id="header" class="header"></div>

        <div id="body2" class="divs">
            <h1 id="tituloPrincipal">Rover RTK</h1>


            <div id="configuracoes" class="visivel">
                <div id="configuracaoRadio" class="divs bordas">

                    <div id="frequenciaRadio" class="optionsRadio">
                        <p class="titulo">Frequencia do rádio</p>
                        <div id="frequenciaValor">
                            <input type="number" class="input" min="430" max="470" value="430"> MHZ
                        </div>
                    </div>

                    <div id="velocidadeRadio" class="optionsRadio">
                    
                        <p class="titulo">Velocidade de transmissão</p>

                        <select id="velocidadeRadioSelect" name="velocidade" class="input">
                            <option value="1" selected>1HZ</option>
                            <option value="3">3HZ</option>
                            <option value="5">5HZ</option>
                            <option value="10">10HZ</option>
                        </select>
                    </div>

                </div>

                <div id="options" class="divs bordas">

                    <div id="frequenceDiv" class="optionsDivs">
                        <p class="titulo">Frequência
                        </p>
                        <select id="frequence" name="frequence" class="input" onchange="frequenceHandler()">
                            <option value="1" selected>1HZ</option>
                            <option value="3">3HZ</option>
                            <option value="5">5HZ</option>
                            <option value="10">10HZ</option>
                        </select>
                    </div>

                </div>


                <div id="constelacoes" class="divs bordas">
                    <p class="titulo">Constelações </p>

                    <div id="constelacoesOptions" class="divs">

                        <input type="checkbox" id="GPS" name="constelacoes" value="GPS" checked>
                        <label for="GPS">GPS</label>
                        <br>
                        <input type="checkbox" id="GLONASS" name="constelacoes" value="GLONASS" checked>
                        <label for="GLONASS">GLONASS</label>
                        <br>
                        <input type="checkbox" id="GALILEO" name="constelacoes" value="GALILEO" checked>
                        <label for="GALILEO">GALILEO</label>
                        <br>
                        <input type="checkbox" id="BEIDOU" name="constelacoes" value="BEIDOU" checked>
                        <label for="BEIDOU">BEIDOU</label>
                        <br>
                        <input type="checkbox" id="SBAS" name="constelacoes" value="SBAS">
                        <label for="SBAS">SBAS</label>
                        <br>
                        <input type="checkbox" id="IMES" name="constelacoes" value="IMES">
                        <label for="IMES">IMES</label>
                        <br>
                        <input type="checkbox" id="QZSS" name="constelacoes" value="QZSS">
                        <label for="QZSS">QZSS</label>
                    </div>
                </div>

                <div class="button">
                    <button onclick="sendRequest()" id="botaoNovoTrabalho">Iniciar</button>
                </div>
            </div>






            <div id="status" class="naoVisivel">
                <div id="cota" class="divs bordas">
                    <p id="tituloCota" class="titulo">Cota</p>
                    <div id="cotaQuadro">
                        <p id="cotaValor">000 M</p>
                    </div>
                </div>

                <div id="statusRTK" class="divs">

                    <div id="tituloStatus">Status do RTK: </div>
                    <div id="statusValor">FIX</div>

                </div>
            </div>



        </div>
    </body>    
</html>

)=====";
