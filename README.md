# OTALab-Node-RED

## Esse projeto é uma complementação do Projeto [OTALab](https://github.com/enzocussuol/OTALab/tree/gd/dev/node-red) 

### 0 Dependencies 
   Para esse projeto funcionar são nescessários:
   1. Ter Docker compose instalado. [Docker](https://docs.docker.com/engine/install/ubuntu/)
   2. Ter OTALab instalado e rodando. [OTALab](https://github.com/enzocussuol/OTALab/tree/gd/dev/node-red)  

### 1 Introdução
  O OTALab-Node-RED surgiu da nesceciade de fazer uma interface para o [OTALab](https://github.com/enzocussuol/OTALab/tree/gd/dev/node-red), e com o uso da
  ferramenta do node-red, foi desenvolvida duas interface uma **Administrador** onde se tem acesso a todas as funções da api do OTALab, e uma **Experimentador** 
  onde está dispolibilizado apenas a opção de ver os dispositivos da rede e fazer upload de coódigos para um dispositivo. 

### 2 Containerização com Docker
  Cada interface está em um conteiner,  separando assim completamente o  **Administrador** do **Experimentador**. Em [docker-compose.yaml](https://github.com/gmdardengo/OTALab-Node-RED/blob/main/docker-compose.yaml)
  temos  o arquivo de inicialização dos containers.
  
### 3 Instalação
  Para inicilaizar basta fazer um git clone do projeto 
  `git clone https://github.com/gmdardengo/OTALab-Node-RED.git`
  E depois no terminal na pasta raiz do projeto digitar `docker-compose up`.

### 4 Uso
  Para acessar o flow editor do **Administrador**  acesse (http://127.0.0.1:1880/) e para acessar o dashboard (http://127.0.0.1:1880/ui)
  
  Para acessar o flow editor do **Experimentador**  acesse (http://127.0.0.1:1881/) e para acessar o dashboard  (http://127.0.0.1:1881/ui)
