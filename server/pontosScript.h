//Página de scripts da página de pontos do servidor    
char PONTOS_SCRIPT[] PROGMEM = R"=====(
async  function novoPonto(){

    var dataJson = {
        Nome: document.getElementById('nomePonto').value,
        Descricao: document.getElementById('descPonto').value
    };

    console.log(dataJson);

    // Realiza o POST request e verifica se foi bem sucedido
    await fetch('/novoPonto', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify(dataJson)
    })
    .then(response => {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }else{
            closePopupPonto();
            clearDataPonto();
            disableButton();
            showMessage("Registrando ponto...");
        }
    }).catch(error => {
        console.error('There has been a problem with your fetch operation:', error);
    });
}


function getPontos(){
    fetch("/getPontos", {
        method: "GET",
        headers: {
            "Content-Type": "application/json"
        }
    }).then(function(response) {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }

        if (response.status == 204) {
            document.getElementById("listaPontos").innerHTML = "Nenhum ponto registrado";
            return;
        }
        return response.json();
    }).then(function(pontos) {
        if(pontos){
            listarPontos(pontos);
        }
    }).catch(error => {
        console.error('There has been a problem with your fetch operation:', error);
    });
}


function listarPontos(pontos){

    document.getElementById("listaPontos").innerHTML = "Nenhum ponto registrado";
    var html = "";

    pontos["Pontos"].forEach(ponto => {
        html += "<div class='ponto'>";
        html += "<div class='pontoNome'>" + ponto["Ponto"] + "</div>";
        html += "</div>";
    });

    document.getElementById("listaPontos").innerHTML = html;
}


function incluirPontoLista(nome){
    var html = "";
    html += "<div class='ponto'>";
    html += "<div class='pontoNome'>" + nome + "</div>";
    html += "</div>";

    if(document.getElementById("listaPontos").innerHTML == "Nenhum ponto registrado"){
        document.getElementById("listaPontos").innerHTML = html;
    }else{
        document.getElementById("listaPontos").innerHTML += html;
    }
}

async function pontoReferencia(){
    // Mostra alerta confirmando a ação
    if(!confirm("Deseja definir o ponto atual como ponto de referência?")){
        return;
    }
    
    // Realiza o POST request e verifica se foi bem sucedido
    await fetch('/cotaReferencia?Ponto=' + document.getElementById("cotaValor").innerHTML, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        }
    })
    .then(response => {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }else{
            showMessage("Registrando cota de referencia...");
        }
    }).catch(error => {
        console.error('There has been a problem with your fetch operation:', error);
    });
}



// Função para habilitar o botão de novo ponto
function enableButton(){
    document.getElementById('botaoNovoPonto').disabled = false;
    document.getElementById('botaoNovoPonto').className = '';

    document.getElementById('botaoNovaConfig').disabled = false;
    document.getElementById('botaoNovaConfig').className = '';
}


// Função para desabilitar o botão de novo ponto
function disableButton(){
    document.getElementById('botaoNovoPonto').disabled = true;
    document.getElementById('botaoNovoPonto').className = 'disabled';
}


function showPopupPonto() {
    document.getElementById("popupAlertPonto").style.display = "block";
}

function closePopupPonto() {
    document.getElementById("popupAlertPonto").style.display = "none";
}

function hidePopupPonto(event) {
    if (event.target == document.getElementById("popupAlertPonto")) {
        closePopupPonto();
    }
}

function cancelDataPonto() {
    clearDataPonto();
    closePopupPonto();
}

function clearDataPonto() {
  document.getElementById('nomePonto').value = '';
  document.getElementById('descPonto').value = '';
}

)=====";
