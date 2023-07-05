#!/bin/bash

# Script para transformar os arquivos do servidor em strings,
# salvas em arquivos .h, para serem usadas no servidor

# Configuração para parar o script caso algum comando falhe
set -e

echo "Gerando arquivos .h do servidor..."
echo ""

echo "Removendo arquivos .h antigos..."
rm server/*.h

echo "Removendo arquivos .h antigos... OK"
echo ""
echo ""

sh serverHTML.sh
sh serverCSS.sh
sh serverJS.sh


# Página de teste de comunicação do servidor (teste.html) | APENAS PARA TESTES INTERNO | 
set +e

# Verifica se o arquivo existe para nao mostrar erro
if [ -f pages/teste.html ]; then
    start='//Página de scripts do servidor
    char TESTE[] PROGMEM = R"=====(
    '

    end='

    )=====";'

    file="$start$(<pages/teste.html)$end"
    echo "$file" >| server/TESTE.h
fi



echo "Arquivos .h do servidor gerados com sucesso!"