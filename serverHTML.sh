
# ========== Arquivos HTML ========== 
echo "Gerando arquivos .html em arquivos .h..."
echo ""



# Página inicial do servidor (index.html)
echo "Gerando index.h..."

start='//Página inicial do servidor
char INDEX_PAGE[] PROGMEM = R"=====(
    
'
end='

)=====";'

file="$start$(<pages/index.html)$end"
echo "$file" >| server/index.h
echo "Gerando index.h... OK"


# Header do servidor (header.html)
echo "Gerando header.h..."

start='//Header das página do servidor
char HEADER_PAGE[] PROGMEM = R"=====(
    
'
end='

)=====";'
file="$start$(<pages/header.html)$end"
echo "$file" >| server/header.h
echo "Gerando header.h... OK"


# PopUp do servidor (popupAlert.html)
echo "Gerando popupAlert.h..."

start='//PopUp do servidor
char POPUPALERTFIX_PAGE[] PROGMEM = R"=====(
    
'
end='

)=====";'
file="$start$(<pages/popupAlertFix.html)$end"
echo "$file" >| server/popupAlertFix.h
echo "Gerando popupAlertFix.h... OK"


# Página de arquivos do servidor (arquivos.html)
echo "Gerando arquivos.h..."

start='//Página de arquivos do servidor
char ARQUIVOS_PAGE[] PROGMEM = R"=====(
    
'
end='

)=====";'

file="$start$(<pages/arquivos.html)$end"
echo "$file" >| server/arquivos.h
echo "Gerando arquivos.h... OK"


echo "Gerando arquivos .html em arquivos .h... OK"
echo ""
echo ""
echo ""