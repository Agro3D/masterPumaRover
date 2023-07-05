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

        var status = event.data;

        //  verifica qual pagina o usuario esta a partir de um pedaco da url
        if (window.location.href.indexOf("arquivos") > -1) {
            switch(status) {
                case 'Conectado':
                    enableButtons();
                    break;
                case 'refreshStatus':
                    await loadFiles();
                    enableButtons();
                    break;
                default:
                    console.log('Nenhuma ação definida');
                    break;
            }
        } else{
            switch(status) {
                case 'Conectado':
                    checkStatus();
                    break;
                case 'Esperando':
                    configurarEsperando();
                    break;
                case 'Pesquisando':
                    configurarPesquisando();
                    break;
                case 'Processando':
                    configurarProcessando();
                    break;
                case 'Salvando':
                    console.log('Salvando');
                    break;

                case 'refreshStatus':
                checkStatus();
                break;
                
                default:
                    console.log('Nenhuma ação definida');
                    break;
            }
        }
    };
};

)=====";
