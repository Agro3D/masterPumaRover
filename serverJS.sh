
# ========== Arquivos JS ==========
echo "Gerando arquivos .js em arquivos .h..."
echo ""

# Página de scripts gloval do servidor (globalScript.js)
echo "Gerando globalScript.h..."

start='//Página de scripts do servidor
char GLOBAL_SCRIPT[] PROGMEM = R"=====(
    
'
end='

)=====";'

file="$start$(<pages/scripts/global.js)$end"
echo "$file" >| server/globalScript.h
echo "Gerando globalScript.h... OK"


# Página de scripts da pagina inicial de configuracao do servidor (indexConfig.js)
echo "Gerando indexConfigScript.h..."

start='//Página de scripts da página inicial do servidor
char INDEX_CONFIG_SCRIPT[] PROGMEM = R"=====(
    
'
end='

)=====";'

file="$start$(<pages/scripts/indexConfig.js)$end"
echo "$file" >| server/indexConfigScript.h
echo "Gerando indexConfigScript.h... OK"



# Página de scripts da pagina inicial de status do servidor (indexStatus.js)
echo "Gerando indexStatusScript.h..."

start='//Página de scripts da página inicial do servidor
char INDEX_STATUS_SCRIPT[] PROGMEM = R"=====(
    
'
end='

)=====";'

file="$start$(<pages/scripts/indexStatus.js)$end"
echo "$file" >| server/indexSTATUSScript.h
echo "Gerando indexStatusScript.h... OK"



# Página de scripts do servidor (script.js)
echo "Gerando pontosScripts.h..."

start='//Página de scripts da página de pontos do servidor    
char PONTOS_SCRIPT[] PROGMEM = R"=====(
'
end='

)=====";'

file="$start$(<pages/scripts/pontos.js)$end"
echo "$file" >| server/pontosScript.h
echo "Gerando pontosScript.h... OK"


# Página de scripts do Websocket (websocket.js)
echo "Gerando webSocketScripts.h..."

start='//Página de scripts do WebSocket
char WEBSOCKET_SCRIPT[] PROGMEM = R"=====(
'
end='

)=====";'

file="$start$(<pages/scripts/webSocket.js)$end"
echo "$file" >| server/webSocketScript.h
echo "Gerando webSocketScript.h... OK"


# Página de scripts do sinal de radio (sinalRadio.js)
echo "Gerando sinalRadioScripts.h..."

start='//Página de scripts do sinal de radio
char SINAL_RADIO_SCRIPT[] PROGMEM = R"=====(
'
end='

)=====";'

file="$start$(<pages/scripts/sinalRadio.js)$end"
echo "$file" >| server/sinalRadioScript.h
echo "Gerando 


echo "Gerando arquivos .js em arquivos .h... OK"
echo ""
echo ""
echo ""