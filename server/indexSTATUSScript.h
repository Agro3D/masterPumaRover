//Página de scripts da página inicial do servidor
char INDEX_STATUS_SCRIPT[] PROGMEM = R"=====(
    
function finalizarTrabalho() {
    document.getElementById("configuracoes").className = "visivel";
    document.getElementById("status").className = "naoVisivel";

    document.getElementById("cotaValor").innerHTML = "000,000";
    document.getElementById("cotaBotao").innerHTML = "Cota <br /> Referencia <br /> <br /> ";
    document.getElementsByClassName("latlonValor")[0].innerHTML = "Carregando...";
    document.getElementsByClassName("latlonValor")[1].innerHTML = "Carregando...";
    document.getElementById("precisaoHorizontalValor").innerHTML = "Carregando...";
    document.getElementById("precisaoVerticalValor").innerHTML = "Carregando...";
    document.getElementById("statusRTKValor").innerHTML = "Carregando...";
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

            switch (text) {
                case 'Esperando':
                    break;
                    
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


function getCotaReferencia(){
    fetch("/getCotaReferencia", {
        method: "GET",
        headers: {
            "Content-Type": "application/json"
        }
    }).then(function(response) {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }

        response.text().then(function(text) {
            document.getElementById("cotaBotao").innerHTML = "Cota <br /> Referencia <br /> <br /> " + text;
        });
    }).catch(error => {
        console.error('There has been a problem with your fetch operation:', error);
    });

}



function atualizaCota(valor) {
    document.getElementById("cotaValor").innerHTML = valor + " M";
}

function atualizaStatusRTK(valor) {
    
    switch(valor) {
        
        case 0:
            document.getElementById('statusRTKValor').innerHTML = 'Sem Sinal';
            document.getElementById('statusRTKValor').className = 'informacoesValor vermelho';
            break;
        
        case 1:
            document.getElementById('statusRTKValor').innerHTML = 'No Fix';
            document.getElementById('statusRTKValor').className = 'informacoesValor vermelho';
            break;
            
        case 2:
            document.getElementById('statusRTKValor').innerHTML = 'No Fix';
            document.getElementById('statusRTKValor').className = 'informacoesValor vermelho';
            break;
                
        case 4:
            document.getElementById('statusRTKValor').innerHTML = 'Fix';
            document.getElementById('statusRTKValor').className = 'informacoesValor verde';
            break;
                
        case 5:
            document.getElementById('statusRTKValor').innerHTML = 'Float';
            document.getElementById('statusRTKValor').className = 'informacoesValor amarelo';
            break;

        default:
            document.getElementById("statusRTKValor").innerHTML = "ERRO";
            document.getElementById("statusRTKValor").className = "informacoesValor vermelho";
            break;
    }
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
