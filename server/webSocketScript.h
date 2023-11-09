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
        // console.log('Server: ', event.data);

        if (event.data == 'Conectado') {
            if (window.location.href == 'http://192.168.4.1/') {    enableButton(); }
            return;
        }

        if (event.data == 'ESPERANDO' || event.data == 'TRABALHANDO') { return; }

        // Transform event.data to json
        console.log(event.data);
        var data = JSON.parse(event.data);
        var mensagem = data['Mensagem'];
        var valor = data['Valor'];

        switch(mensagem) {
            case 'Cota':
                document.getElementById('cotaValor').innerHTML = valor.toFixed(3);
                if (data['Status'] == "CERTO")
                    document.getElementById('cotaQuadro').className = 'cotaCerta';
                else
                    document.getElementById('cotaQuadro').className = 'cotaErrada';
                break;

            case 'LAT_LON':
                document.getElementsByClassName('latlonValor')[0].innerHTML = valor["lat"];
                document.getElementsByClassName('latlonValor')[1].innerHTML = valor["lon"];
                break;
            
            case 'RTK':
                atualizaStatusRTK(parseInt(valor));
                break;

            case 'PRECISAO':
                document.getElementById('precisaoVerticalValor').innerHTML = "Vertical " + valor["precisaoVertical"] + ' M';
                document.getElementById('precisaoHorizontalValor').innerHTML = "Horizontal " + valor["precisaoHorizontal"] + ' M';
                break;

            case 'NOVO_PONTO':
                incluirPontoLista(valor);
                enableButton();
                break;

            case 'LISTAR_PONTOS':
                listarPontos(valor);
                break;

            case 'LISTAR_ARQUIVOS':
                listarArquivos(valor['Pastas']);
                break;

            case 'ALERT_MESSAGE':
                showMessage(valor['Mensagem'], valor['Cor']);
                enableButton();
                break;

            case 'SINAL_RADIO':
                atualizaSinalRadio(valor);
                break;

            case 'COTA_REFERENCIA':
                document.getElementById("cotaBotao").innerHTML = "Cota <br /> Referencia <br /> <br /> " + valor + " M";
                break;

            default:
                console.log('Nenhuma ação definida');
                break;
        }
    };
};

)=====";
