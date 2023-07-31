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
        <link rel="stylesheet" type="text/css" href="styles/indexConfig.css">
        <link rel="stylesheet" type="text/css" href="styles/indexStatus.css">
        <link rel="stylesheet" type="text/css" href="styles/popupAlert.css">

        <script src="scripts/webSocket.js"></script>
        <script src="scripts/global.js"></script>
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
                <div id="configuracaoRadio" class="divs bordas">

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

                <div id="options" class="divs bordas">

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
                
                
                <div class="divs bordas">
                    
                    <div id="arquivos">
                        
                        
                        <div class="arquivosDivs">
                            
                            <p class="titulo">Arquivos</p>
                            
                            <select name="arquivos" id="arquivosSelect" onchange="arquivoChange()" class="input inputSelect inputContent">
                                <option value="0" selected disabled>Selecione um arquivo</option>
                                <option value="1">Criar um novo Arquivo...</option>
                            </select>
                            
                        </div>
                        
                        <div class="arquivosDivs">
                            
                            <p class="titulo">Nome do Arquivos</p>
                            <input type="text" id="nomeArquivo" class="input inputContent inputContent" placeholder="Nome do arquivo" disabled>
                            
                        </div>
                        
                    </div>

                    <div id="obs">
                        Obs: Deixe em branco para criar um arquivo com data e hora atual(YYYY-MM-DD_HH:MM).
                    </div>
                </div>

                <div class="button">
                    <button onclick="novoTrabalho()" id="botaoNovaConfig">Iniciar</button>
                </div>
            </div>



            
            <!-- Tela de status -->
            <div id="status" class="naoVisivel">
                <div id="cota" class="divs bordas">
                    <p id="tituloCota" class="titulo">Cota</p>
                    <div id="cotaQuadro">
                        <p id="cotaValor">000,000</p>
                    </div>
                </div>

                <div id="informacoes" class="divs">

                    <div class="informacoesDivs">
                        <div class="informacoesTitulos">Status do RTK: </div>
                        <div id="statusRTKValor" class="informacoesValor">Carregando</div>
                    </div>

                    <div class="informacoesDivs">
                        <div class="informacoesTitulos">Precisão posicional: </div>
                        <div id="precisaoValor" class="informacoesValor">Carregando</div>
                    </div>

                </div>


                <div class="button">
                    <button onclick="voltar()" id="botaoCancelar">Voltar</button>
                </div>
                
                
                <div class="divs bordas listaPontos">
                    <h1 id="tituloPrincipal">Lista de Pontos</h1>
                    <div class="button">
                        <button onclick="showPopup()" id="botaoNovoPonto" class="disabled" >Novo Ponto</button>
                    </div>

                    <div id="listaPontos">
                        Carregando...

                    </div>
                
                </div>
            
            </div>


            <!-- PopUp Novo Ponto-->
            <div id="popupAlert" class="popup" onclick="hidePopup(event)">
                <div class="popup-content">
                    <label for="name">Nome:</label><br>
                    <input type="text" id="nomePonto" name="namePonto" class="inputPopup" placeholder="Escreva aqui o nome do ponto"><br>
                    <label for="desc">Descrição:</label><br>
                    <textarea id="descPonto" name="descPonto" class="inputPopup textareaPopup" placeholder="Escreva aqui a descrição do ponto"></textarea>

                    <div id="botoesPopup">
                        <button id="cancel" class="botaoPopup" onclick="cancelData()">Cancelar</button>
                        <button id="save" class="botaoPopup" onclick="novoPonto()">Salvar</button>
                    </div>

                </div>
              </div>


              <!-- Alerta de mensagem -->
              <div id="messageAlert" class="message">Ponto criado com sucesso!</div>
              
              



            <!-- Temporario para testes -->
            <div class="button">
                <button onclick="troca()" id="troca">Troca</button>
            </div>



        </div>
    </body>    
</html>

)=====";
