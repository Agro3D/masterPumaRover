//Página de scripts do servidor
char GLOBAL_SCRIPT[] PROGMEM = R"=====(
    
// ==================== Funções para importar os componentes ====================
function imports(){

    // Importa o header da pagina
    let xhttpHeader = new XMLHttpRequest();
    elementHeader = document.getElementById("header");
    let header = "header.html";

    if (header){
        xhttpHeader.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
                elementHeader.innerHTML = this.responseText;
            }
        };
        xhttpHeader.open("GET", header, true);
        xhttpHeader.send();
    }
    
}




// ==================== Funções para o popup ====================
function verificaCartaoSD(){

    // Verifica o tamanho da lista de arquivos
    fetch("/getCartaoSD", {
        method: "GET",
        headers: {
            "Content-Type": "application/json"
        }
    }).then(function(response) {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }

        response.text().then(function(text) {
            if (text == 0){
                newPopup("cartaoSD", text);
            }
        });
    })
    .catch(error => {
        console.error('There has been a problem with your fetch operation:', error);
    });
}


function newPopup(mensagem, dado){
    
    // Importa o popup para a pagina
    let xhttpPopup = new XMLHttpRequest();
    elementPopup = document.getElementsByTagName("body")[0];
    let popup = "popupAlertFix.html";

    if (popup){
        xhttpPopup.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
                elementPopup.innerHTML += this.responseText;
            }
        };
        xhttpPopup.open("GET", popup, true);
        xhttpPopup.send();
    }

    setTimeout(function(){
        document.getElementById("messageAlertFix").className = "messageFix show"; /* Mostrar a mensagem */
        document.getElementById("messageAlertFix").style.backgroundColor = "#a011ff"; /* Muda a cor do fundo */
        
        if(mensagem == "cartaoSD"){
            // Mostra a mensagem de alerta para o cartão SD
            document.getElementById("messageAlertFix").style.backgroundColor = "#CC2020"; /* Muda a cor do fundo */
            document.getElementById("messageAlertFixText").innerHTML = `Cartão SD não foi detectado. Por favor,
                                                                    insira um cartão SD e reinicie o aparelho.`; /* Mostrar a mensagem */
        }
    }, 200);
}


function closePopup(){
    document.getElementById("messageAlertFix").className = "message hide"; /* Esconder a mensagem */
}




// ==================== Funções para o menu mobile ====================

// Função para mostrar/esconder o menu mobile
function toggleMenu() {
    var menu = document.getElementById("mobileMenu");
    if (menu.style.display === "flex") {
        menu.style.display = "none";
    } else {
        menu.style.display = "flex";
    }
}


// Função para fechar o menu mobile ao clicar fora dele
window.onclick = function(event) {
    var menu = document.getElementById('mobileMenu');
    if (!event.target.matches('#mobileMenu') && !event.target.matches('#menuIcon')) {
        menu.style.display = 'none';
    }
}

)=====";
