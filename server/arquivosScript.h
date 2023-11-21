//Página de scripts da pagina de arquivos do servidor
char ARQUIVOS_SCRIPT[] PROGMEM = R"=====(

window.onload = loadFiles();

async function loadFiles(){
    // Realiza o POST request com o objeto dataJson
    await fetch('/getFiles', {
        method: 'get',
        headers: {
            'Content-Type': 'application/json',
        }
    })
    .then(response => {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        return response.json();
    })
    .then(function(json) {
        // A variável 'json' agora contém o seu JSON como um objeto JavaScript.

        var html = '';
        json['Pastas'].forEach(function(fileItem) {
                html += '<div class="file">'; // Inicia a div do arquivo
                
                html += '<div class="informationFile">';
                html += '<div class="nameFile">' + fileItem["Arquivo"] + '</div>'; // Adiciona o arquivo
                html += '<div class="sizeFile">' + fileItem["Tamanho"] + '</div>'; // Adiciona o arquivo
                html += '</div>'; // Finaliza a div das informações
                
                html += '<div class="optionsFile">';
                html += `<button class="btnDownload" onClick="window.open('http://192.168.4.184/downloadFile?Arquivo=` + fileItem["Arquivo"] + `')" disabled>Download</button>`; // Adiciona o arquivo
                html += `<button class="btnExcluir"  onClick="deletarArquivo('` + fileItem["Arquivo"] + `')" disabled>Excluir</button>`; // Adiciona o arquivo
                html += '</div>'; // Finaliza a div do download
                
                html += '</div>'; // Finaliza a div do arquivo        
        });
        
        // Agora nós temos uma string HTML que podemos adicionar ao nosso elemento de ID "arquivos"
        document.getElementById("archives").innerHTML = html;

        // document.getElementById("arquivos").innerHTML = JSON.stringify(json);

    })
    .catch(error => {
        console.error('There has been a problem with your fetch operation:', error);
    });
}


function enableButtons() {
    // Seleciona todos os botões
    var buttons = document.getElementsByTagName("button");
    
    // Itera sobre todos os botões e remove o atributo "disabled"
    for (var i = 0; i < buttons.length; i++) {
      buttons[i].removeAttribute("disabled");
    }
  }
  


function deletarArquivo(Arquivo){
    var r = confirm("Deseja realmente excluir o arquivo " + Arquivo + "?");
    if (r == true) {
        // Realiza o POST request com o objeto dataJson

        fetch('/deleteFile?Arquivo=' + Arquivo, {
            method: 'post',
            headers: {
                'Content-Type': 'application/json',
            }
        })
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            return response.json();
        })
        .catch(error => {
            console.error('There has been a problem with your fetch operation:', error);
        });
    }
}

)=====";
