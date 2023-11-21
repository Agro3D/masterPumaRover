//Página de scripts para os pontos do servidor
char PONTOS_SCRIPT[] PROGMEM = R"=====(
async  function novoPonto(){

    var dataJson = {
        Nome: document.getElementById('nomePonto').value,
        Descricao: document.getElementById('descPonto').value
    };

    closePopupPonto();
    console.log(dataJson);

    // Realiza o POST request e verifica se foi bem sucedido
    await fetch('/novoPonto', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify(dataJson)
    }).then(response => {
        if (!response.ok) {
            showMessage("Erro ao registrar ponto <br /> Vereifique a conexão");
            throw new Error('Network response was not ok');
        }else{
            clearDataPonto();
            showMessage("Registrando ponto... <br /> Mantenha o aparelho imóvel.");
        }
    }).catch(error => {
        console.error('There has been a problem with your fetch operation:', error);
        showMessage("Erro ao registrar ponto <br /> Vereifique a conexão ou reinicie o aparelho");
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
            document.getElementById("listaPontos").innerHTML = "Nenhum ponto registrado";
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


function listarPontos(pontos){

    document.getElementById("listaPontos").innerHTML = "Nenhum ponto registrado";
    var html = "";

    pontos["Pontos"].forEach(ponto => {
        html += "<div class='ponto' onclick='expandPonto(this)'>";
        html += "<div class='pontoNome'>" + ponto["Ponto"] + "</div>";
        html += "<div class='pontoDescricao'>" + ponto["Descricao"] + "</div>";
        html += "</div>";
    });

    document.getElementById("listaPontos").innerHTML = html;
}


function incluirPontoLista(ponto){
    var html = "";
    html += "<div class='ponto' onclick='expandPonto(this)'>";
    html += "<div class='pontoNome'>" + ponto["Ponto"] + "</div>";
    if(ponto["Descricao"])
        html += "<div class='pontoDescricao'>" + ponto["Descricao"].replace(/\n/g, "<br />") + "</div>";
    else
        html += "<div class='pontoDescricao'>Sem descrição</div>";
    html += "</div>";
    
    if(document.getElementById("listaPontos").innerHTML == "Nenhum ponto registrado" || 
    document.getElementById("listaPontos").innerHTML == "Carregando..." ){
        document.getElementById("listaPontos").innerHTML = html;
    }else{
        document.getElementById("listaPontos").innerHTML += html;
    }
}

async function pontoReferencia(){
    // Mostra alerta confirmando a ação
    let resposta = prompt("Deseja definir o ponto atual como ponto de referência?",
                            document.getElementById("cotaValor").innerHTML);
                            
    if(resposta == null || resposta == ""){ return; }
    
    // Realiza o POST request e verifica se foi bem sucedido
    await fetch('/cotaReferencia?Ponto=' + resposta, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        }
    })
    .then(response => {
        if (!response.ok) {
            showMessage("Erro ao registrar cota de referência <br /> Vereifique a conexão");
            throw new Error('Network response was not ok');
        }else{
            showMessage("Cota de referencia salva", "verde");
            document.getElementById("cotaBotao").innerHTML = "Cota <br /> Referencia <br /> <br /> " + resposta;
        }
    }).catch(error => {
        showMessage("Erro ao registrar cota de referência <br /> Vereifique a conexão ou reinicie o aparelho");
        console.error('There has been a problem with your fetch operation:', error);
    });
}



// Função para habilitar o botão de novo ponto
function enableButton(){
    document.getElementById('botaoNovoPonto').disabled = false;
    document.getElementById('botaoNovoPonto').className = '';

    document.getElementById('botaoNovaConfig').disabled = false;
    document.getElementById('botaoNovaConfig').className = '';
}


// Função para desabilitar o botão de novo ponto
function disableButton(){
    document.getElementById('botaoNovoPonto').disabled = true;
    document.getElementById('botaoNovoPonto').className = 'disabled';
}


function showPopupPonto() {
    document.getElementById("popupAlertPonto").style.display = "block";
}

function closePopupPonto() {
    document.getElementById("popupAlertPonto").style.display = "none";
}

function hidePopupPonto(event) {
    if (event.target == document.getElementById("popupAlertPonto")) {
        closePopupPonto();
    }
}

function cancelDataPonto() {
    clearDataPonto();
    closePopupPonto();
}

function clearDataPonto() {
  document.getElementById('nomePonto').value = '';
  document.getElementById('descPonto').value = '';
}


function expandPonto(divPonto){
    var listaPontos = document.getElementsByClassName("pontoDescricao");
    var pontoDescricao = divPonto.getElementsByClassName("pontoDescricao")[0];
    
    for (var i = 0; i < listaPontos.length; i++) {
        if(listaPontos[i] == pontoDescricao)
            if(pontoDescricao.style.display == "block"){
                recolher(pontoDescricao);
            }else{
                expandir(pontoDescricao);
            }
        else{
            recolher(listaPontos[i]);
        }
    }
}


function expandir(div){
    // Calcula a altura da div para a animação de expandir

    var heightInicial = div.parentElement.clientHeight * 0.9 + "px";
    div.style.display = "block";
    var heightFinal = div.parentElement.clientHeight * 0.92 + "px";
    div.style.display = "none";
    
    // Define a altura da div para a animação de expandir
    var r = document.querySelector(':root');
    r.style.setProperty('--alturaExpandirInicial', heightInicial);
    r.style.setProperty('--alturaExpandirFinal', heightFinal);
    
    div.parentElement.classList.add("expandir");
    div.parentElement.classList.remove("recolher");
    div.style.display = "block";
}


function recolher(div){

    // Caso a div não esteja expandida, não faz nada
    if(!div.parentElement.classList.contains("expandir")){
        return;
    }
    
    // Calcula a altura da div para a animação de expandir
    var heightInicial = div.parentElement.clientHeight * 0.9 + "px";
    div.style.display = "none";
    var heightFinal = div.parentElement.clientHeight * 0.65 + "px";
    div.style.display = "block";
    
    // Define a altura da div para a animação de expandir
    var r = document.querySelector(':root');
    r.style.setProperty('--alturaRecolherInicial', heightInicial);
    r.style.setProperty('--alturaRecolherFinal', heightFinal);

    div.parentElement.classList.remove("expandir");
    div.parentElement.classList.add("recolher");
    div.style.display = "none";
}
 

)=====";
