//Página inicial do servidor
char INDEX_PAGE[] PROGMEM = R"=====(
    
<!DOCTYPE html>
<html>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <head>
        <title>Puma Station Web Server</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <meta charset="UTF-8">

        <link rel="stylesheet" type="text/css" href="styles/global.css">
        <link rel="stylesheet" type="text/css" href="styles/header.css">
        <link rel="stylesheet" type="text/css" href="styles/sinalRadio.css">

        <link rel="stylesheet" type="text/css" href="styles/indexConfig.css">
        <link rel="stylesheet" type="text/css" href="styles/indexStatus.css">

        <link rel="stylesheet" type="text/css" href="styles/listaPontos.css">
        <link rel="stylesheet" type="text/css" href="styles/popupAlert.css">
        <link rel="stylesheet" type="text/css" href="styles/popupAlertFix.css">

        <script src="scripts/webSocket.js"></script>
        <script src="scripts/global.js"></script>
        <script src="scripts/sinalRadio.js"></script>

        <script src="scripts/indexConfig.js"></script>
        <script src="scripts/indexStatus.js"></script>

        <script src="scripts/pontos.js"></script>
    </head>

    <body onload="initIndex()">
        <div id="header" class="header"></div>

        <div id="body2" class="divs">
            <h1 id="tituloPrincipal">Rover RTK</h1>



            <!-- Tela de configurações -->
            <div id="configuracoes" class="visivel">
                <!-- <div class="divs bordas">
                    <p class="titulo tituloPrincipal">Rádio</p>

                    <div id="configuracaoRadio">
                    
                        <div id="frequenciaRadio" class="optionsRadio">
                            <p class="titulo">Frequencia do rádio</p>
                            <div id="frequenciaValor">
                                <input type="number" id="frequenciaRadioValor" class="input" min="430" max="470" value="430"> MHZ
                            </div>
                        </div>
                    
                        <div id="velocidadeRadio" class="optionsRadio">
                        
                            <p class="titulo">Velocidade de transmissão</p>
                        
                            <select id="velocidadeRadioSelect" name="velocidade" class="input inputSelect">
                                <option value="1" selected>1HZ</option>
                                <option value="3">3HZ</option>
                                <option value="5">5HZ</option>
                                <option value="10">10HZ</option>
                            </select>
                        </div>
                    
                    </div>
                </div> -->

                <!-- <div id="options" class="divs bordas">
                    <p class="titulo tituloPrincipal">GNSS
                    <div id="options">

                        <div id="frequenceDiv" class="optionsDivs">
                            <p class="titulo">Taxa de Atualização
                            </p>
                            <select id="frequenciaTransmissao" name="frequence" class="input inputSelect">
                                <option value="1" selected>1HZ</option>
                                <option value="3">3HZ</option>
                                <option value="5">5HZ</option>
                                <option value="10">10HZ</option>
                            </select>
                        </div>

                    </div>


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
                </div> -->
                
                
                <!-- <div class="divs">
                    <div id="bastaoDiv">

                        <p class="titulo">Altura do Bastão</p>

                        <div id="alturaBastaoDiv">
                            <input type="number" name="alturaBastao" id="alturaBastao"
                            placeholder="Altura do Bastão" class="input inputText"
                            value="2" min="0" max="100" step="0.1"> M
                        </div>
                            
                    </div>
                </div> -->


                <div class="divs bordas">
                    
                    <div id="arquivos">
                        
                        
                        <div class="arquivosDivs">
                            
                            <p class="titulo">Trabalhos Anteriores</p>
                            
                            <select name="arquivos" id="arquivosSelect" class="input inputSelect inputContent">
                                <option value="0" selected disabled>Selecione um Trabalho</option>
                                <option value="1">Criar um novo Trabalho...</option>
                            </select>
                            
                        </div>
                        
                        <div class="arquivosDivs">
                            
                            <p class="titulo">Criar novo Trabalho</p>
                            <button onclick="showPopupArquivo()" id="botaoNovoArquivo">Novo Trabalho</button>
                            
                        </div>
                        
                    </div>
                </div>

                <div class="button">
                    <button onclick="novoTrabalho()" id="botaoNovaConfig" class="disabled" disabled>
                        Iniciar
                    </button>
                </div>
            </div>


            <!-- PopUp Novo Arquivo-->
            <div id="popupAlertArquivo" class="popup" onclick="hidePopupArquivo(event)">
                <div class="popup-content">
                    <label for="name">Nome:</label><br>
                    <input type="text" id="nomeArquivo" name="nameArquivo" class="inputPopup" placeholder="Nome do Arquivo"><br>

                    <div id="obs">
                        Obs: Deixar em branco, salvará o arquivo com a data e hora atual (AAAA-MM-DD_HH:MM.kml).
                    </div>

                    <div id="botoesPopup">
                        <button id="cancel" class="botaoPopup" onclick="cancelDataArquivo()">Cancelar</button>
                        <button id="save" class="botaoPopup" onclick="novoArquivo()">Salvar</button>
                    </div>

                </div>
            </div>


            
            <!-- Tela de status -->
            <div id="status" class="naoVisivel">
                
                <div id="cota" class="divs bordas">

                    <div id="cotaQuadro" class="cotaErrada">
                        <p id="tituloCota" class="titulo">Cota:</p>
                        <p id="cotaValor">000,000</p>
                    </div>
                    
                    <div id="cotaReferencia">
                        <button id="cotaBotao" onclick="pontoReferencia()">Cota <br /> Referencia <br /> <br /></button>
                    </div>

                </div>
                                
                <div id="latlon" class="divs">
                    <div id="latitude" class="latlonDiv">
                        <div class="latLonTitulo">
                            latitude:
                        </div>
                        <div class="latlonValor">
                            Carregando...
                        </div>
                    </div>
                    
                    <div id="longitude" class="latlonDiv">
                        <div class="latLonTitulo">
                            longitude:
                        </div>
                        <div class="latlonValor">
                            Carregando...
                        </div>
                    </div>
                </div>


                <div id="informacoes" class="divs">
                    <div id="informacoesDiv">
                        <div class="informacaoDiv">
                            <div class="informacoesTitulos">RTK: </div>
                            <div class="informacoesTitulos">Precisão: </div>
                        </div>
                        
                        <div class="informacaoDiv">
                            <div id="statusRTKValor" class="informacoesValor">Carregando...</div>
                            <div class="informacoesValor">
                                <div id="precisaoHorizontalValor">Carregando...</div>
                                <div id="precisaoVerticalValor">Carregando...</div>
                            </div>
                        </div>
                    </div>
                    
                    <div class="button">
                        <button onclick="finalizarTrabalho()" id="botaoFinalizar"> Finalizar </br> Trabalho </button>
                    </div>
                </div>


                
                
                <div class="divs bordas listaPontos">
                    
                    <div id="novoPonto">
                        <button onclick="showPopupPonto()" id="botaoNovoPonto" class="disabled" disabled>Coletar Ponto</button>
                    </div>
                    <h1 id="tituloPrincipal" class="tituloMobile">Lista de Pontos</h1>

                    <div id="listaPontos">
                        Carregando...

                    </div>
                
                </div>
            
            </div>


            <!-- PopUp Novo Ponto-->
            <div id="popupAlertPonto" class="popup" onclick="hidePopupPonto(event)">
                <div class="popup-content">
                    <label for="name">Nome:</label><br>
                    <input type="text" id="nomePonto" name="namePonto" class="inputPopup" placeholder="Escreva aqui o nome do ponto"><br>
                    <label for="desc">Descrição:</label><br>
                    <textarea id="descPonto" name="descPonto" class="inputPopup textareaPopup" placeholder="Escreva aqui a descrição do ponto"></textarea>

                    <div id="botoesPopup">
                        <button id="cancel" class="botaoPopup" onclick="cancelDataPonto()">Cancelar</button>
                        <button id="save" class="botaoPopup" onclick="novoPonto()">Salvar</button>
                    </div>

                </div>
            </div>


              <!-- Alerta de mensagem -->
              <div id="messageAlert" class="message">Carregando</div>
              
              



            <!-- Temporario para testes -->
            <div class="button">
                <button onclick="troca()" id="troca">Troca</button>
            </div>



        </div>
    </body>    
</html>

)=====";
