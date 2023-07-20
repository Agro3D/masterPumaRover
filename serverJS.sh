
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


# Página de scripts da pagina inicial do servidor (index.js)
echo "Gerando indexScript.h..."

start='//Página de scripts da página inicial do servidor
char INDEX_SCRIPT[] PROGMEM = R"=====(
    
'
end='

)=====";'

file="$start$(<pages/scripts/index.js)$end"
echo "$file" >| server/indexScript.h
echo "Gerando indexScript.h... OK"



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


echo "Gerando arquivos .js em arquivos .h... OK"
echo ""
echo ""
echo ""