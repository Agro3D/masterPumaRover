
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


# Página de estilos da página inicial do servidor (indexStyle.css)
echo "Gerando indexStyle.h..."

start='//Página de estilos da página inicial do servidor
char INDEX_STYLE[] PROGMEM = R"=====(

'
end='

)=====";'

file="$start$(<pages/styles/index.css)$end"
echo "$file" >| server/indexStyle.h
echo "Gerando indexStyle.h... OK"


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