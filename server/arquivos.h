//Página de arquivos do servidor
char ARQUIVOS_PAGE[] PROGMEM = R"=====(
    
<!DOCTYPE html>
<html>
    <head>
        <title>Puma Station Web Server</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <meta charset="UTF-8">

        <link rel="stylesheet" type="text/css" href="styles/global.css">
        <link rel="stylesheet" type="text/css" href="styles/header.css">
        <link rel="stylesheet" type="text/css" href="styles/arquivos.css">
        
        <script src="scripts/webSocket.js"></script>
        <script src="scripts/global.js"></script>
        <script src="scripts/arquivos.js"></script>
    </head>

    <body onload="imports();startWebSocket();">

        <div id="header" class="header"></div>
        

        <div id="body2" class="divs">
            <h1 id="tituloPrincipal">Arquivos</h1>

            <div class="divs bordas">
                <div id="archives">

                </div>
            </div>

            

        </div>
    </body>    
</html>

)=====";
