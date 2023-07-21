//Página de scripts da página de pontos do servidor    
char PONTOS_SCRIPT[] PROGMEM = R"=====(
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

)=====";
