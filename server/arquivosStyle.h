//Página de estilos da página inicial do servidor
char ARQUIVOS_STYLE[] PROGMEM = R"=====(

#archives{
    margin: 2vw;
    padding: 1vw;
    border: 1px solid #bbb;
    border-radius: 5px;
    background-color: #fff;
    box-shadow: 0px 0px 5px #bbb;  
    color: #000; 
}

.folderName{
    border-bottom: 1px solid #bbb;
}
.file{
    margin-left: 2vw;
    margin-bottom: 2vh;
    font-size: medium;
    display: flex;
    align-content: center;
    flex-direction: row;
    justify-content: space-between;
    align-items: baseline;
    border-bottom: 1px solid #bbb;
}

.optionsFile{
    font-size: small;
    margin-right: 1vw;
    display: flex;
    flex-direction: column;
    align-items: flex-end;
}
    
.sizeFile{
    margin-left: 1vw;
    margin-bottom: 2vh;
    font-size: small;
    color: #444;
}

.file:hover{
    background-color: #eee;
}

.btnDownload{
    background-color: #fff;
    border: none;
    color: #000;
    font-size: small;
    font-weight: bold;
    cursor: pointer;
    padding: 3px 10px;
    background-color: #65c55c;
    border: 1px solid #bbb;
    border-radius: 5px;
    margin: 0.5vh 0;
}

.btnDownload:hover{
    background-color: #387e32;
    color: #fff;
}

.btnDownload:disabled{
    color: #666;
    cursor: default;
}

.btnDownload:disabled:hover{
    background-color: #65c55c;
    color: #666;
}

.btnExcluir{
    background-color: #fff;
    border: none;
    color: #000;
    font-size: small;
    font-weight: bold;
    cursor: pointer;
    padding: 3px 10px;
    background-color: #e95c5c;
    border: 1px solid #bbb;
    border-radius: 5px;
    margin: 0.5vh 0;
}

.btnExcluir:hover{
    background-color: #992929;
    color: #fff;
}

.btnExcluir:disabled{
    color: #666;
    cursor: default;
}

.btnExcluir:disabled:hover{
    background-color: #e95c5c;
    color: #666;
}


@media screen and (max-width: 400px) {
    #body2{
        min-width: 80vw;
    }
}

@media screen and (min-width: 400px) and (max-width: 600px) {
    #body2{
        min-width: 75vw;
    }
    
}

)=====";
