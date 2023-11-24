//Página de scripts da página inicial do servidor
char INDEX_CONFIG_SCRIPT[] PROGMEM = R"=====(
    
function initIndex(){
    imports();
    startWebSocket();
    getStatus();
    getFiles();
    getPontos();
    getCotaReferencia();
    verificaCartaoSD();
    getSinal();
    // newPopup("cartaoSD", 0);
}

function novoTrabalho() {
    document.getElementById("botaoNovaConfig").disabled = true;
    
    var configJson = {};
    // var frequencia = document.getElementById("frequenciaRadioValor").value;

    // if (frequencia == ""){
    //     alert("Preencha todos os campos")
    //     document.getElementById("configuracoes").className = "visivel";
    //     document.getElementById("status").className = "naoVisivel";
    //     return;
    // }else{
        // configJson.radioFrequencia = frequencia;
        // }

    var numConstelations = 0;
    // Verifica quais constelacoes estao selecionadas e atribui ao objeto configJson
    // var constelations = document.getElementsByName('constelacoes');
    
    // for(var i=0, n=constelations.length; i<n; i++) {
    //     if (constelations[i].checked == true){
    //         configJson[constelations[i].value] = constelations[i].checked;
    //         numConstelations++;
    //     }
    // }
    
    configJson['GPS'] = true;
    configJson['GLONASS'] = true;
    configJson['GALILEO'] = true;
    configJson['BEIDOU'] = true;
    configJson['SBAS'] = false;
    configJson['IMES'] = false;
    configJson['QZSS'] = false;

    // Verifica se ao menos uma constelacao foi selecionada
    // if (numConstelations == 0){
    //     alert("Selecione ao menos uma constelação!");
    //     document.getElementById("configuracoes").className = "visivel";
    //     document.getElementById("status").className = "naoVisivel";
    //     return;
    // }

    // configJson.velocidadeTransmissao = document.getElementById("velocidadeRadioSelect").value;
    // configJson.taxaAtualizacao = document.getElementById("frequenciaTransmissao").value;

    configJson.taxaAtualizacao = 1;

    
    // var alturaBastao = document.getElementById("alturaBastao").value;

    // if (alturaBastao == ""){
    //     configJson.alturaBastao = 0;
    // }else{
    //     configJson.alturaBastao = alturaBastao;
    // }
    
    configJson.alturaBastao = 1.5;

    var NomeArquivo = document.getElementById("arquivosSelect").value;

    if (NomeArquivo != 0 && NomeArquivo != 1) {
        configJson.NomeArquivo = document.getElementById("arquivosSelect").value;
    } else {
        if (NomeArquivo == 0)
        configJson.NomeArquivo = "";
        else{
            configJson.NomeArquivo = document.getElementById("nomeArquivo").value.normalize('NFD').replace(/[\u0300-\u036f]/g, "");
        }
    }

    document.getElementById("cotaValor").innerHTML = "000.000";
    document.getElementById('cotaQuadro').className = 'cotaErrada';
    document.getElementById("cotaBotao").innerHTML = "Cota <br /> Referencia <br /> <br /> ";
    document.getElementsByClassName("latlonValor")[0].innerHTML = "Carregando...";
    document.getElementsByClassName("latlonValor")[1].innerHTML = "Carregando...";
    document.getElementById("precisaoHorizontalValor").innerHTML = "Carregando...";
    document.getElementById("precisaoVerticalValor").innerHTML = "Carregando...";
    document.getElementById("statusRTKValor").innerHTML = "Carregando...";
    document.getElementById("statusRTKValor").className = "informacoesValor";
    

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

    document.getElementById("listaPontos").innerHTML = "Carregando...";


    document.getElementById("frequenciaRadioValor").value = 430;
    document.getElementById("velocidadeRadioSelect").value = 1;

    document.getElementById("frequenciaTransmissao").value = 1;

    document.getElementById("alturaBastao").value = 0;

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

function novoArquivo() {
    document.getElementById("arquivosSelect").value = 1;
    closePopupArquivo();
}

function showPopupArquivo(){
    document.getElementById("popupAlertArquivo").style.display = "block";
}

function closePopupArquivo() {
    document.getElementById("popupAlertArquivo").style.display = "none";
}

function hidePopupArquivo(event) {
    if (event.target == document.getElementById("popupAlertArquivo")) {
        closePopupArquivo();
    }
}

function cancelDataArquivo() {
    document.getElementById('nomeArquivo').value = '';
    document.getElementById("arquivosSelect").value = 0;
    closePopupArquivo();
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

        listarArquivos(json['Pastas']);

    }).catch(error => {
        console.error('There has been a problem with your fetch operation:', error);
    });
}

function listarArquivos(arquivos){
    arquivos.forEach(arquivo => {

        var select = document.getElementById("arquivosSelect");
        var option = document.createElement("option");
        option.text = arquivo["Arquivo"];
        option.value = arquivo["Arquivo"];
        select.appendChild(option);
        
    });
}

)=====";
