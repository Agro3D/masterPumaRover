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
        var mensagem = data['mensagem'];
        var valor = data['valor'];

        switch(mensagem) {
            case 'cota':
                atualizaCota(valor);
                break;
            case 'statusRTK':
                atualizaStatusRTK(valor);
                break;

            default:
                console.log('Nenhuma ação definida');
                break;
        }
    };
};