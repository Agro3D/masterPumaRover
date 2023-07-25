//Página de scripts da página inicial do servidor
char INDEX_SCRIPT[] PROGMEM = R"=====(
    
function voltar() {
    document.getElementById("configuracoes").className = "visivel";
    document.getElementById("status").className = "naoVisivel";

    document.getElementById("cotaValor").innerHTML = "000.000";
    document.getElementById("precisaoValor").innerHTML = "Carregando";
    document.getElementById("statusRTKValor").innerHTML = "Carregando";
    document.getElementById("statusRTKValor").className = "informacoesValor";

    // Realiza o POST para parar o trabalho
    fetch('/pararTrabalho', {
        method: 'GET',
        headers: {
            'Content-Type': 'application/json',
        }
    }).then(response => {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
    }).catch(error => {
        console.error('There has been a problem with your fetch operation:', error);
    });


}



function getStatus(){
    // Verifica o status pelo mestre
    fetch("/getStatus", {
        method: "GET",
        headers: {
            "Content-Type": "application/json"
        }
    }).then(function(response) {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }

        response.text().then(function(text) {

            console.log(text);

            switch (text) {
                case 'Trabalhando':
                    troca();
                    break;

                default:
                    console.log('Nenhuma ação definida');
                    break;
            }
        });
    }).catch(error => {
        console.error('There has been a problem with your fetch operation:', error);
    });
}


function novoTrabalho() {
    document.getElementById("configuracoes").className = "naoVisivel";
    document.getElementById("status").className = "visivel";
    
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
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
    })
    .catch(error => {
        console.error('There has been a problem with your fetch operation:', error);
    });
}


function atualizaCota(valor) {
    document.getElementById("cotaValor").innerHTML = valor + " M";
}

function atualizaStatusRTK(valor) {

    document.getElementById("statusRTKValor").innerHTML = valor;
    
    switch(valor) {
        case 2:
            document.getElementById('statusRTKValor').innerHTML = 'Fix';
            document.getElementById('statusRTKValor').className = 'informacoesValor verde';
            break;
            case 1:
            document.getElementById('statusRTKValor').innerHTML = 'Float';
            document.getElementById('statusRTKValor').className = 'informacoesValor amarelo';
            break;
            case 0:
            document.getElementById('statusRTKValor').innerHTML = 'No Fix';
            document.getElementById('statusRTKValor').className = 'informacoesValor vermelho';
            break;
        default:
            document.getElementById("statusRTKValor").className = "informacoesValor vermelho";
            document.getElementById("statusRTKValor").innerHTML = "ERRO";
            break;
    }
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

)=====";
