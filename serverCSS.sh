
# ========== Arquivos CSS ==========
echo "Gerando arquivos .css em arquivos .h..."
echo ""

# Página de estilos globais do servidor (globalStyle.css)
echo "Gerando globalStyle.h..."

start='//Arquivo de estilos do servidor
char GLOBAL_STYLE[] PROGMEM = R"=====(
    
'
end='

)=====";'

file="$start$(<pages/styles/global.css)$end"
echo "$file" >| server/globalStyle.h
echo "Gerando globalStyle.h... OK"


# Página de estilos do header do servidor (headerStyle.css)
echo "Gerando headerStyle.h..."

start='//Página de estilos do header do servidor
char HEADER_STYLE[] PROGMEM = R"=====(

'
end='

)=====";'

file="$start$(<pages/styles/header.css)$end"
echo "$file" >| server/headerStyle.h
echo "Gerando headerStyle.h... OK"


# Página de estilos das torres de sinal do radio (sinalRadio.css)
echo "Gerando sinalRadio.h..."

start='//Página de estilos das torres de sinal do radio
char SINAL_RADIO_STYLE[] PROGMEM = R"=====(

'
end='

)=====";'

file="$start$(<pages/styles/sinalRadio.css)$end"
echo "$file" >| server/sinalRadioStyle.h
echo "Gerando sinalRadio.h... OK"


# Página de estilos da página inicial do servidor (indexConfigStyle.css)
echo "Gerando indexConfigStyle.h..."

start='//Página de estilos da página inicial do servidor
char INDEX_CONFIG_STYLE[] PROGMEM = R"=====(

'
end='

)=====";'

file="$start$(<pages/styles/indexConfig.css)$end"
echo "$file" >| server/indexConfigStyle.h
echo "Gerando indexConfigStyle.h... OK"
echo "Gerando headerStyle.h... OK"


# Página de estilos da página inicial do servidor (indexStatusStyle.css)
echo "Gerando indexStatusStyle.h..."

start='//Página de estilos da página inicial do servidor
char INDEX_STATUS_STYLE[] PROGMEM = R"=====(

'
end='

)=====";'

file="$start$(<pages/styles/indexStatus.css)$end"
echo "$file" >| server/indexStatusStyle.h
echo "Gerando indexStatusStyle.h... OK"


# Página de estilos da lista de pontos (listaPontosStyle.css)
echo "Gerando listaPontosStyle.h..."

start='//Página de estilos da lista de pontos
char LISTA_PONTOS_STYLE[] PROGMEM = R"=====(

'
end='

)=====";'

file="$start$(<pages/styles/listaPontos.css)$end"
echo "$file" >| server/listaPontosStyle.h
echo "Gerando listaPontosStyle.h... OK"


# Página de estilos do popup de novo ponto (popupStyle.css)
echo "Gerando popupStyle.h..."

start='//Página de estilos do popup de novo ponto
char POPUP_NOVO_PONTO_STYLE[] PROGMEM = R"=====(

'
end='

)=====";'

file="$start$(<pages/styles/popupAlert.css)$end"
echo "$file" >| server/popupStyle.h
echo "Gerando popupStyle.h... OK"



# Página de estilos do popup fixo de avisos (popupStyleFix.css)
echo "Gerando popupFixStyle.h..."

start='//Página de estilos do popup fixo de avisos
char POPUP_FIX_STYLE[] PROGMEM = R"=====(

'
end='

)=====";'

file="$start$(<pages/styles/popupAlertFix.css)$end"
echo "$file" >| server/popupFixStyle.h
echo "Gerando popupFixStyle.h... OK"


# Página de estilos da página inicial do servidor (arquivosStyle.css)
echo "Gerando arquivosStyle.h..."

start='//Página de estilos da página inicial do servidor
char ARQUIVOS_STYLE[] PROGMEM = R"=====(

'
end='

)=====";'

file="$start$(<pages/styles/arquivos.css)$end"
echo "$file" >| server/arquivosStyle.h
echo "Gerando arquivosStyle.h... OK"


echo "Gerando arquivos .css em arquivos .h... OK"
echo ""
echo ""
echo ""