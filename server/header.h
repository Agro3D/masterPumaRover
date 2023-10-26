//Header das página do servidor
char HEADER_PAGE[] PROGMEM = R"=====(
    

    <h1 class="headerTitle"><a href="/">Puma Rover RTK</a></h1>

    <a href="#" id="menuIcon" class="toggle" onclick="toggleMenu()">&#9776;</a>
    <div id="headerLinks">
        <a href="/">Inicio</a>
        <a href="/configuracoes">Configurações</a>
    </div>
    <div id="mobileMenu">
        <a href="/">Inicio</a>
        <a href="/configuracoes">Configurações</a>
    </div>
    <div id="sinalRadio">
        <div id="torres">
            <div id="sinalRadioTorre1" class="comTorre"></div>
            <div id="sinalRadioTorre2" class="comTorre"></div>
            <div id="sinalRadioTorre3" class="comTorre"></div>
            <div id="sinalRadioTorre4" class="comTorre"></div>
        </div>
        <div>
            Rádio
        </div>
    </div>

)=====";
