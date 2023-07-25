async  function novoPonto(){
    // Realiza o POST request e verifica se foi bem sucedido
    await fetch('/novoPonto', {
        method: 'get',
        headers: {
            'Content-Type': 'application/json',
        }
    })
    .then(response => {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }else{
            console.log("Ponto registrado com sucesso!");
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