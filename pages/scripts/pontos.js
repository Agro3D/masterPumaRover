async  function novoPonto(){

    console.log("Iniciando novo ponto...");

    var dataJson = {
        nome: document.getElementById('nomePonto').value,
        descricao: document.getElementById('descPonto').value
    };

    console.log(dataJson);

    // Realiza o POST request e verifica se foi bem sucedido
    await fetch('/novoPonto', {
        method: 'get',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify(dataJson)
    })
    .then(response => {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }else{
            console.log("Ponto registrado com sucesso!");
            closePopup();
            clearData();
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
    document.getElementById("popupNovoPonto").style.display = "block";
}

function closePopup() {
    document.getElementById("popupNovoPonto").style.display = "none";
}

function hidePopup(event) {
    if (event.target == document.getElementById("popupNovoPonto")) {
        document.getElementById("popupNovoPonto").style.display = "none";
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