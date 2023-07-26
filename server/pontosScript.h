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
            showMessage("Registrando ponto...");
        }
    }).catch(error => {
        console.error('There has been a problem with your fetch operation:', error);
    });
}


// Função para habilitar o botão de novo ponto
function enableButton(){
    document.getElementById('botaoNovoPonto').disabled = false;
    document.getElementById('botaoNovoPonto').className = '';
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

function showMessage(message, cor) {
    if(cor == 'verde'){
        document.getElementById("messageAlert").style.backgroundColor = "#2b8f17";
    }else if(cor == 'vermelho'){
        document.getElementById("messageAlert").style.backgroundColor = "#f44336";
    }else{
        document.getElementById("messageAlert").style.backgroundColor = "#a011ff";
    }

    document.getElementById("messageAlert").innerHTML = message;
    document.getElementById("messageAlert").className = "message show"; /* Mostrar a mensagem */
    setTimeout(function(){ document.getElementById("messageAlert").className = "message"; }, 3000); /* Esconder após 3 segundos */
  }

)=====";
