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

        // Transform event.data to json
        var data = JSON.parse(event.data);
        var mensagem = data['Mensagem'];
        var valor = data['Valor'];

        switch(mensagem) {
            case 'Cota':
                document.getElementById('cotaValor').innerHTML = valor;
                break;
            
            case 'RTK':
                if(valor == 0) {
                    document.getElementById('statusRTKValor').innerHTML = 'No Fix';
                    document.getElementById('statusRTKValor').className = 'informacoesValor vermelho';
                }else if(valor == 1) {
                    document.getElementById('statusRTKValor').innerHTML = 'Float';
                    document.getElementById('statusRTKValor').className = 'informacoesValor amarelo';
                }else if(valor == 2) {
                    document.getElementById('statusRTKValor').innerHTML = 'Fix';
                    document.getElementById('statusRTKValor').className = 'informacoesValor verde';
                }
                break;

            case 'Precisao':
                document.getElementById('precisaoValor').innerHTML = valor;
                break;

            default:
                console.log('Nenhuma ação definida');
                break;
        }
    };
};