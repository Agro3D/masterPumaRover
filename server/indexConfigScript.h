//Página de scripts da página inicial do servidor
char INDEX_CONFIG_SCRIPT[] PROGMEM = R"=====(
    
function initIndex(){
    imports();
    startWebSocket();
    getStatus();
    getFiles();
    getPontos();
}

function novoTrabalho() {
    document.getElementById("botaoNovaConfig").disabled = true;
    
    var configJson = {};
    var frequencia = document.getElementById("frequenciaRadioValor").value;

    if (frequencia == ""){
        alert("Preencha todos os campos")
        document.getElementById("configuracoes").className = "visivel";
        document.getElementById("status").className = "naoVisivel";
        return;
    }else{
        configJson.radioFrequencia = frequencia;
    }


    var numConstelations = 0;
    // Verifica quais constelacoes estao selecionadas e atribui ao objeto configJson
    var constelations = document.getElementsByName('constelacoes');
    
    for(var i=0, n=constelations.length; i<n; i++) {
        if (constelations[i].checked == true){
            configJson[constelations[i].value] = constelations[i].checked;
            numConstelations++;
        }
    }
    

    // Verifica se ao menos uma constelacao foi selecionada
    if (numConstelations == 0){
        alert("Selecione ao menos uma constelação!");
        document.getElementById("configuracoes").className = "visivel";
        document.getElementById("status").className = "naoVisivel";
        return;
    }

    configJson.velocidadeTransmissao = document.getElementById("velocidadeRadioSelect").value;
    configJson.taxaAtualizacao = document.getElementById("frequenciaTransmissao").value;

    var NomeArquivo = document.getElementById("arquivosSelect").value;

    if (NomeArquivo != 0 && NomeArquivo != 1) {
        configJson.NomeArquivo = document.getElementById("arquivosSelect").value;
    } else {
        if (NomeArquivo == 0)
        configJson.NomeArquivo = "";
        else{
            configJson.NomeArquivo = document.getElementById("nomeArquivo").value;
        }
    }


    console.log(configJson);

    // Realiza o POST request com o objeto dataJson
    fetch('/postConfiguration', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify(configJson),
    })
    .then(response => {
        document.getElementById("botaoNovaConfig").disabled = false;
        if (!response.ok) {
            throw new Error('Network response was not ok');
        } else{
            limparConteudo();
        }

    })
    .catch(error => {
        console.error('There has been a problem with your fetch operation:', error);
    });
}


function limparConteudo(){
    document.getElementById("configuracoes").className = "naoVisivel";
    document.getElementById("status").className = "visivel";

    document.getElementById("frequenciaRadioValor").value = 430;
    document.getElementById("velocidadeRadioSelect").value = 1;

    document.getElementById("frequenciaTransmissao").value = 1;

    document.getElementById("GPS").checked = true;
    document.getElementById("GLONASS").checked = true;
    document.getElementById("GALILEO").checked = true;
    document.getElementById("BEIDOU").checked = true;
    document.getElementById("SBAS").checked = false;
    document.getElementById("IMES").checked = false;
    document.getElementById("QZSS").checked = false;

    document.getElementById("arquivosSelect").value = 0;
    document.getElementById("nomeArquivo").value = "";
}


function troca(){
    if(document.getElementById("status").className == "naoVisivel"){
        document.getElementById("configuracoes").className = "naoVisivel";
        document.getElementById("status").className = "flvisivelex";
    }else{
        document.getElementById("configuracoes").className = "visivel";
        document.getElementById("status").className = "naoVisivel";
    }
}

function arquivoChange(){
    if (document.getElementById("arquivosSelect").value == 1)
        document.getElementById("nomeArquivo").disabled = false;
    else
        document.getElementById("nomeArquivo").disabled = true;
}


function getFiles(){
    fetch("/getFiles", {
        method: "GET",
        headers: {
            "Content-Type": "application/json"
        }
    }).then(function(response) {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }

        return response.json();
    }).then(function(json) {

        json.forEach(arquivo => {

            var select = document.getElementById("arquivosSelect");
            var option = document.createElement("option");
            option.text = arquivo["Arquivo"];
            option.value = arquivo["Arquivo"];
            select.appendChild(option);
            
        });

    }).catch(error => {
        console.error('There has been a problem with your fetch operation:', error);
    });
}

)=====";
