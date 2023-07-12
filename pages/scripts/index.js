function voltar() {
    document.getElementById("configuracoes").style.display = "block";
    document.getElementById("status").style.display = "none";
}


function novoTrabalho() {
    document.getElementById("configuracoes").style.display = "none";
    document.getElementById("status").style.display = "block";
    
    var configJson = {};
    var frequencia = document.getElementById("frequenciaRadioValor").value;

    if (frequencia == ""){
        alert("Preencha todos os campos")
        document.getElementById("configuracoes").style.display = "block";
        document.getElementById("status").style.display = "none";
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
        document.getElementById("configuracoes").style.display = "block";
        document.getElementById("status").style.display = "none";
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
        body: JSON.stringify(dataJson),
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
        case 'FIX':
            document.getElementById("statusRTKValor").className = "verde";
            break;
        case 'FLOAT':
            document.getElementById("statusRTKValor").className = "yellow";
            break;
        case 'NO FIX':
            document.getElementById("statusRTKValor").className = "red";
            break;
        default:
            document.getElementById("statusRTKValor").className = "red";
            document.getElementById("statusRTKValor").innerHTML = "ERRO";
            break;
    }
}