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

        if (event.data == 'ESPERANDO' || event.data == 'TRABALHANDO') { return; }

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

            case 'PRECISAO':
                document.getElementById('precisaoValor').innerHTML = valor + ' mm';
                break;

            case 'LISTAR_PONTOS':
                console.log('LISTAR_PONTOS');
                listarPontos(valor);
                break;

            case 'ALERT_MESSAGE':
                console.log("ALERT_MESSAGE");

                console.log(event.data);
                console.log(data);
                console.log(mensagem);
                console.log(valor);
                // var alerta = JSON.parse(valor);
                // console.log(alerta);
                showMessage(valor["Mensagem"], valor["Cor"]);
                enableButton();
                break;

            default:
                console.log('Nenhuma ação definida');
                break;
        }
    };
};