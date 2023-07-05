# Master Puma Station
Este repositório abriga o código-fonte para o servidor principal ESP32-S3 em nosso sistema integrado de gerenciamento e comunicação de antena. O servidor é projetado para gerenciar um segundo módulo ESP32-S3, cuja função é configurar e facilitar a comunicação com uma antena.

## Descrição
Este servidor, baseado no módulo ESP32-S3, é acessível através de um ponto de acesso dedicado. Ele gerencia o segundo dispositivo ESP32-S3, encarregado de configurar e estabelecer comunicação com uma antena específica. Juntos, eles fornecem um fluxo de dados eficiente e consistente, essencial para qualquer aplicação que requer comunicação de alta velocidade e confiabilidade.

## Começando
### Pré-requisitos
- 2 Hardware ESP32-S3
- Firmware adequado
- Antena compatível

### Instalação
1. Faça o clone deste repositório para o seu ambiente local.
2. Faça o download do código-fonte do módulo ESP32-S3 secundário.
3. Conecte o módulo ESP32-S3 secundário ao servidor principal.
4. Conecte o módulo ESP32-S3 secundário a uma antena compatível.
5. Compile e carregue o código para o servidor ESP32-S3.
6. Compile e carregue o código para o módulo ESP32-S3 secundário.

### Uso
Este servidor gerencia um módulo ESP32-S3 secundário que é responsável pela comunicação com a antena. Certifique-se de que a antena está configurada corretamente para permitir uma comunicação eficaz. Para conectar-se ao servidor, conecte-se ao ponto de acesso dedicado (_http://192.168.4.1_) e acesse o endereço IP do servidor. O servidor fornecerá uma interface de usuário para configurar e gerenciar o módulo ESP32-S3 secundário.


### Licença


### Contato
Se você tiver alguma dúvida ou sugestão, sinta-se à vontade para entrar em contato conosco através de email.

Obrigado por seu interesse e apoio ao nosso projeto!
