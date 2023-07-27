//Página de scripts do WebSocket
char WEBSOCKET_SCRIPT[] PROGMEM = R"=====(
function startWebSocket() {
    // Delay para iniciar o WebSocket
    setTimeout(function(){
        // Inicia o WebSocket
        initWebSocket();
    }, 1000);
}

function initWebSocket() {
    console.log('Iniciando WebSocket');
    var ws = new WebSocket('ws://192.168.4.1:81/');
    console.log('WebSocket Iniciado');
    
    ws.onopen = function() {
        ws.send('Hello from client');
    };

    ws.onmessage = async function (event) {
        console.log('Server: ', event.data);

        if (event.data == 'Conectado') {

            if (window.location.href == 'http://192.168.4.1/') {    enableButton(); }
            
            return;
        }

        // Transform event.data to json
        var data = JSON.parse(event.data);
        var mensagem = data['Mensagem'];
        var valor = data['Valor'];

        switch(mensagem) {
            case 'Cota':
                document.getElementById('cotaValor').innerHTML = valor.toFixed(3);
                break;
            
            case 'RTK':
                atualizaStatusRTK(valor);
                break;

            case 'Precisao':
                document.getElementById('precisaoValor').innerHTML = valor + ' mm';
                break;

            case 'NOVO_PONTO':
                if (valor == 'OK') {
                    showMessage('Ponto registrado com sucesso!', 'verde');
                } else if (valor == 'ERRO') {
                    showMessage('Erro ao registrar ponto!', 'vermelho');
                } else {
                    showMessage('Erro desconhecido ao registrar ponto!', 'vermelho');
                }
                enableButton();
            default:
                console.log('Nenhuma ação definida');
                break;
        }
    };
};

)=====";
