function getSinal(){
     // Verifica os sinais de radio pelo mestre
     fetch("/getSinalRadio", {
        method: "GET",
        headers: {
            "Content-Type": "application/json"
        }
    }).then(function(response) {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }

        response.text().then(function(valor) { atualizaSinalRadio(valor);});
    }).catch(error => {
        console.error('There has been a problem with your fetch operation:', error);
    });
}


function atualizaSinalRadio(valor){
    // Pega os 4 elementos de torre de sinal da página pelo id e colocar em um array
    var elementos = document.querySelectorAll(`#sinalRadioTorre1, #sinalRadioTorre2,
                                                #sinalRadioTorre3, #sinalRadioTorre4`);

    // Percorre o array e altera a classe dos elementos de acordo com o valor passado
    for(var i = 0; i < elementos.length; i++){
        if(i < valor)
            elementos[i].className = "comTorre";
        else
            elementos[i].className = "semTorre";
    }
}