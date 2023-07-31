//Página de scripts da página de pontos do servidor    
char PONTOS_SCRIPT[] PROGMEM = R"=====(
async  function novoPonto(){

    console.log("Iniciando novo ponto...");

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
            console.log("Requisição de novo ponto enviada com sucesso!");
            closePopup();
            clearData();
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

    document.getElementById("listaPontos").innerHTML = "";
    var html = "";
    
    pontos["Pontos"].forEach(ponto => {
        html += "<div class='ponto'>";
        html += "<div class='pontoNome'>" + ponto["Ponto"] + "</div>";
        html += "</div>";
        
    });

    document.getElementById("listaPontos").innerHTML = html;
}


// Função para habilitar o botão de novo ponto
function enableButton(){
    document.getElementById('botaoNovoPonto').disabled = false;
    document.getElementById('botaoNovoPonto').className = '';
}


// Função para desabilitar o botão de novo ponto
function disableButton(){
    document.getElementById('botaoNovoPonto').disabled = true;
    document.getElementById('botaoNovoPonto').className = 'disabled';
}


function showPopup() {
    document.getElementById("popupAlert").style.display = "block";
}

function closePopup() {
    document.getElementById("popupAlert").style.display = "none";
}

function hidePopup(event) {
    if (event.target == document.getElementById("popupAlert")) {
        document.getElementById("popupAlert").style.display = "none";
    }
}

function cancelData() {
    clearData();
    closePopup();
}

function clearData() {
  document.getElementById('nomePonto').value = '';
  document.getElementById('descPonto').value = '';
}

)=====";
