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