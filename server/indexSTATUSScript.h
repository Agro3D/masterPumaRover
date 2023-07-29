//Página de scripts da página inicial do servidor
char INDEX_STATUS_SCRIPT[] PROGMEM = R"=====(
    
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
            document.getElementById("archives").innerHTML = "Nenhum ponto registrado";
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


function atualizaCota(valor) {
    document.getElementById("cotaValor").innerHTML = valor + " M";
}

function atualizaStatusRTK(valor) {

    consoler.log("StatusRKT: ", valor);
    
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


function listarPontos(pontos){

    document.getElementById("archives").innerHTML = "";
    
    pontos["Pontos"].forEach(ponto => {
        document.getElementById("archives").innerHTML += ponto["Ponto"];
        document.getElementById("archives").innerHTML += "</br>";
    });
}

)=====";
