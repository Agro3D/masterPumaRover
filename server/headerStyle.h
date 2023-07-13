//Página de estilos do header do servidor
char HEADER_STYLE[] PROGMEM = R"=====(

.header {
    width: 100vw;
    height: 6vh;
    display: flex;
    align-items: center;
    background-color: #333;
    color: white;
    position: fixed;
    top: 0;
    z-index: 1000;
}

.headerTitle {
    margin: 0;
    text-align: center;
    flex-grow: 1;
}

.headerTitle a {
    color: white;
    text-decoration: none;
}

.toggle {
    display: none;
}

#mobileMenu {
    display: none;
}

#headerLinks{
    position: absolute;
    margin-left: 20px;
}

#headerLinks a {
    color: white;
    text-decoration: none;
    margin-right: 15px;
}

#headerLinks a:hover {
    color: #33da00;
}



@media (max-width: 768px) {
    #headerLinks{
        display: none;
    }

    .toggle {
        display: block;
        position: absolute;        
        left: 3vw;
        color: white;
        text-decoration: none;
        font-size: xx-large;
    }

    #mobileMenu {
        display: none;
        flex-direction: column;
        position: absolute;
        top: 0;
        left: 0;
        margin-top: 6vh;
        margin-left: 1vw;
        padding: 2%;
        border: 1px solid #4c0677;
        border-radius: 10%;
        background-color: #333;
        text-decoration: none;
        color: white;
        font-size: 1rem;
        line-height: 1.3;
    }

    #mobileMenu a {
        color: white;
        text-decoration: none;
        margin-right: 15px;
    }

}

)=====";